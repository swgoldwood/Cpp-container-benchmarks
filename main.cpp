#include <benchmark/benchmark.h>
#include <list>
#include <unordered_set>

constexpr int64_t START_SIZE = 8;
constexpr int64_t END_SIZE = 8 << 12;
constexpr int64_t MAX_ELEMENTS = 8 << 22;
constexpr int64_t MAX_CONTAINERS = 8 << 12;

static int64_t toIncrement = 0;

template<typename T, bool scattered = false>
class BaseFixture : public benchmark::Fixture
{
public:
    virtual void push( T& con, int64_t elem ) = 0;

    virtual int64_t find( T& con, int64_t elem ) = 0;

    void SetUp( const benchmark::State& state )
    {
        size_t containersSize = scattered ? std::min( MAX_ELEMENTS / state.range( 0 ), MAX_CONTAINERS ) : 1;
        containers_.resize( containersSize );

        for( size_t c = 0; c < containers_.size(); c++ )
        {
            for( int64_t i = 0; i < state.range( 0 ); i++ )
                push( containers_[ c ], i );
        }
    }

    void TearDown( const benchmark::State& state )
    {
        containers_.clear();
    }

    void bench( benchmark::State& state )
    {
        for( auto _: state )
        {
            if constexpr( scattered )
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

template<typename T, bool scattered = false>
class VecListFixture : public BaseFixture<T, scattered>
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

template<typename T, bool scattered = false>
class SetHashFixture : public BaseFixture<T, scattered>
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
BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, VectorTest, std::vector<int64_t> )( benchmark::State& state )
{
    bench( state );
}
BENCHMARK_REGISTER_F( VecListFixture, VectorTest )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, ListTest, std::list<int64_t> )( benchmark::State& state )
{
    bench( state );
}
BENCHMARK_REGISTER_F( VecListFixture, ListTest )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, SetTest, std::set<int64_t> )( benchmark::State& state )
{
    bench( state );
}
BENCHMARK_REGISTER_F( SetHashFixture, SetTest )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, HashTest, std::unordered_set<int64_t> )( benchmark::State& state )
{
    bench( state );
}
BENCHMARK_REGISTER_F( SetHashFixture, HashTest )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

/*
 * Now test with scattered = true, which simulates a real world application where data is unlikely to be
 * any of the CPU caches.
 */
BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, VectorTestScattered, std::vector<int64_t>, true )( benchmark::State& state )
{
    bench( state );
}
BENCHMARK_REGISTER_F( VecListFixture, VectorTestScattered )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( VecListFixture, ListTestScattered, std::list<int64_t>, true )( benchmark::State& state )
{
    bench( state );
}
BENCHMARK_REGISTER_F( VecListFixture, ListTestScattered )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, SetTestScattered, std::set<int64_t>, true )( benchmark::State& state )
{
    bench( state );
}
BENCHMARK_REGISTER_F( SetHashFixture, SetTestScattered )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_TEMPLATE_DEFINE_F( SetHashFixture, HashTestScattered, std::unordered_set<int64_t>, true )( benchmark::State& state )
{
    bench( state );
}
BENCHMARK_REGISTER_F( SetHashFixture, HashTestScattered )->RangeMultiplier( 2 )->Range( START_SIZE, END_SIZE );

BENCHMARK_MAIN();
