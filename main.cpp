#include <benchmark/benchmark.h>
#include <list>
#include <unordered_set>
#include <numeric>
#include <algorithm>
#include <random>

constexpr int64_t START_SIZE = 8;
constexpr int64_t END_SIZE = 8 << 12;
constexpr int64_t MAX_CONTAINERS = 8 << 12;
constexpr int64_t MAX_ELEMENTS = 8 << 22;

static int64_t toIncrement = 0;

template<typename T, bool scatterAccess = false, bool scatterInsertion = false>
class BaseFixture : public benchmark::Fixture
{
public:
    virtual void push( T& con, int64_t elem ) {}

    virtual int64_t find( T& con, int64_t elem ) { return 0; }

    void SetUp( const benchmark::State& state )
    {
        int64_t containerSize = state.range( 0 );
        size_t containersSize = scatterAccess ? std::min( MAX_ELEMENTS / state.range( 0 ), MAX_CONTAINERS ) : 1;

        if( containers_.size() == containersSize && containers_[0].size() == containerSize )
            return;

        containers_.clear();
        containers_.resize( containersSize );

        if( !scatterAccess || !scatterInsertion )
        {
            for( auto& container: containers_ )
            {
                for( int64_t i = 0; i < state.range( 0 ); i++ )
                    push( container, i );
            }
        }
        else
        {
            //seed random to ensure insertion order is same across all benchmarks
            srand( 0 );
            //jumble up the insertion order of elements in each container
            for( int64_t i = 0; i < state.range( 0 ); i++ )
            {
                std::vector<size_t> idxs( containers_.size() );
                std::iota( idxs.begin(), idxs.end(), 0 );
                auto rng = std::default_random_engine {};
                std::shuffle( idxs.begin(), idxs.end(), rng );

                for( size_t idx: idxs )
                    push( containers_[idx], i );
            }
        }
    }

    void TearDown( const benchmark::State& state )
    {
        //don't teardown to speed things up
    }

    void bench( benchmark::State& state )
    {
        //again seed random so fair benchmarking
        srand( 0 );
        for( auto _: state )
        {
            if constexpr( scatterAccess )
            {
                size_t idx = rand() % containers_.size();
                toIncrement = find( containers_[ idx ], int64_t( rand() % state.range( 0 ) ) );
            }
            else
                toIncrement += find( containers_[ 0 ], int64_t( rand() % state.range( 0 ) ) );
        }
    }

    std::vector<T> containers_;
};

template<typename T, bool scatter = false, bool scatterWrites = false>
class VecListFixture : public BaseFixture<T, scatter, scatterWrites>
{
public:
    void push( T& con, int64_t elem ) override
    {
        con.push_back( elem );
    }

    int64_t find( T& con, int64_t elem ) override
    {
        return *std::find( con.begin(), con.end(), elem );
    }
};

template<typename T, bool scatter = false, bool scatterWrites = false>
class SetHashFixture : public BaseFixture<T, scatter, scatterWrites>
{
public:
    void push( T& con, int64_t elem ) override
    {
        con.insert( elem );
    }

    int64_t find( T& con, int64_t elem ) override
    {
        return *con.find( elem );
    }
};

/*
 * Simple benchmark test, testing a single container at a time for Vector, List, Set, and Unordered_Set
 */
BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, Vector, std::vector<int64_t> )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( VecListFixture, Vector )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, List, std::list<int64_t> )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( VecListFixture, List )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, Set, std::set<int64_t> )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( SetHashFixture, Set )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, Hash, std::unordered_set<int64_t> )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( SetHashFixture, Hash )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

/*
 * Now test with scatter = true, which simulates a real world application by randomizing reads across
 * many containers, so data is unlikely to be in cache
 */
BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, VectorScatterReads, std::vector<int64_t>, true )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( VecListFixture, VectorScatterReads )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, ListScatterReads, std::list<int64_t>, true )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( VecListFixture, ListScatterReads )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, SetScatterReads, std::set<int64_t>, true )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( SetHashFixture, SetScatterReads )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, HashScatterReads, std::unordered_set<int64_t>, true )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( SetHashFixture, HashScatterReads )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

/*
 * As well as scattering reads, scatter the writes so that the m number of containers are written to at random, until each
 * has n number of elements
 */
BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, VectorScatterRW, std::vector<int64_t>, true, true )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( VecListFixture, VectorScatterRW )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, ListScatterRW, std::list<int64_t>, true, true )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( VecListFixture, ListScatterRW )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, SetScatterRW, std::set<int64_t>, true, true )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( SetHashFixture, SetScatterRW )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, HashScatterRW, std::unordered_set<int64_t>, true, true )( benchmark::State& state ) { bench( state ); }
BENCHMARK_REGISTER_F( SetHashFixture, HashScatterRW )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_MAIN();
