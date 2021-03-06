#include <iostream>
#include <type_traits>
using namespace std;



static const int32_t MAX_ROW = 4;
static const int32_t MAX_COL = 5;

namespace VECTOR_UNROLL_integral_const
{
//unrolled function
template<int32_t N>
void display_row()
{
    std::cout<<"row "<<N<<std::endl;
}

//terminate case
void unroll_vector(std::integral_constant<int32_t, MAX_ROW>) {}

template<int32_t N = 0>
void unroll_vector(std::integral_constant<int32_t, N >)
{
    display_row<N>();
    unroll_vector(std::integral_constant<int32_t, N + 1>());
}

void unroll_vector()
{
    unroll_vector(std::integral_constant<int32_t, 0>());
}

}


namespace MATRIX_UNROLL_integral_const
{

template<int32_t row, int32_t col>
void display_matrix_item()
{
    std::cout<<"row "<<row<<" col "<<col<<std::endl;
}

template<int32_t row>
void unroll_col(std::integral_constant<int32_t, MAX_COL>){}

template<int32_t row, int32_t col>
void unroll_col(std::integral_constant<int32_t, col>)
{
    display_matrix_item<row,col>();
    unroll_col<row>(std::integral_constant<int32_t, col + 1>());
}



template<int32_t row>
void unroll_col_helper()
{
    unroll_col<row>(std::integral_constant<int32_t, 0>());
}

void unroll_row(std::integral_constant<int32_t,MAX_ROW>){}

template<int32_t row>
void unroll_row(std::integral_constant<int32_t,row>)
{
    unroll_col_helper<row>();    
    unroll_row(std::integral_constant<int32_t,row + 1>());
}

void unroll_matrix()
{
    unroll_row(std::integral_constant<int32_t, 0>());
}
}

#include <iostream>
#include <type_traits>
using namespace std;

namespace VECTOR_UNROLL_boost
{
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/copy.hpp>
struct value_printer
{
    template< typename U > void operator()(U x)
    {
        std::cout << x << '\n';
    }
};

void unroll_loop()
{
    boost::mpl::for_each< boost::mpl::range_c<int,0,MAX_ROW> >( value_printer() );
}
}


int main()
{
    VECTOR_UNROLL_1::unroll_loop();
    return 1;
}
