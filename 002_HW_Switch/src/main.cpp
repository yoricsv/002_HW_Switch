#include "main.h"

// DEFINE ENUMERATION CONSTANTS FOR SWITCH MANAGING BEGIN //
enum PROGRAM_STATE
{
    CHOOSE_A_STATE,
    ENTER_NUM,
    LOOP_NUM,
    COUNT_NUM,
    EXIT
};// DEFINE ENUMERATION CONSTANTS FOR SWITCH MANAGING END //

// AUXILIARY VARIABLES BEGIN //
constexpr    auto     LOOPS           = 2;
static       bool     selected_loop   = false;
             uint32_t get_number      = 0;
             uint32_t port_state      = 0;
             uint32_t output          = 0;
static       uint32_t program_state   = 0;
static       uint32_t ranks           = 0;
static       uint32_t cnt_number      = 0;
static       uint32_t numBuffer       = 0;
static       uint32_t numBufferMax    = 50;
static       uint32_t mask            = 0xfff;
static const uint32_t RANK_SELECTOR[] =
{
    0x100, 0x200, 0x400, 0x800
};
static const uint32_t DECIMAL_NUMBERS_DECODER[] =
{
    0x3f, 0x06, 0x5b, 0x4f, 0x66,
    0x6d, 0x7d, 0x07, 0x7f, 0x6f
};
static const uint32_t MAX_RANKS       = sizeof(RANK_SELECTOR)           / sizeof(uint32_t);
static const uint32_t MAX_NUMBERS     = sizeof(DECIMAL_NUMBERS_DECODER) / sizeof(uint32_t);
// AUXILIARY VARIABLES END //

static void set_indicator(  uint32_t port_value,
                            uint32_t rank)
{
    /*
        ******************************************************************
        * LOGIC:                                                         *
        * get a port_state like 0x 0000 0000 0101 1011                   *
        * mask = 0x 0000 1111 1111 1111 (allowed change bits)            *
        * ~mask = 0x 1111 0000 0000 0000 (invert for set remain bits)    *
        * result = result & ~mask                                        *
        * result = result \ port_state (modify 7-bits 0101 1011)         *
        * result -> 0x 0000 0000 0101 1011                               *
        ******************************************************************
    */
    output = (port_value & ~mask)
        | RANK_SELECTOR[rank % MAX_RANKS]
        | DECIMAL_NUMBERS_DECODER[port_value % MAX_NUMBERS];
    std::cout << "\nPort value for MCU (hexadecimal format)\t -> 0x  0000 0000 0000 0" << std::hex << output;
    std::cout << "\nPort value for MCU (binary format)\t -> 0b ";
    convert_to_binary(output);
 } // SET INDICATOR FUNCTION END //

// SPLIT FUNCTION BEGIN //
void splitNumber_byRank(uint32_t get_value)
{
    numBuffer = get_value;
    do
    {
        uint32_t tmp = numBuffer % 10;
        set_indicator(tmp, ranks);
        numBuffer /= 10;
        if (ranks < MAX_RANKS)
            ranks++;
        else
            ranks = 0;
    } while (numBuffer > 0);
    ranks = 0;
}
// SPLIT FUNCTION END //

int main()
{
    while (true)
    {
        switch (program_state)
        {
            case (CHOOSE_A_STATE):
            {
                std::cout << "\nSelect the status of the program:"              << std::endl;
                std::cout << "\t1: Enter a number for display it dynamically,"  << std::endl;
                std::cout << "\t2: Dynamically display a number in a loop,"     << std::endl;
                std::cout << "\t3: Activate a counter from 0 to "               << LOOPS;
                std::cout << " that dynamically displays each number."          << std::endl;
                std::cout << "What will you choose?"                            << std::endl;

                std::cin  >> program_state;
                switch (program_state)
                {
                    case ENTER_NUM: program_state = ENTER_NUM; break;
                    case LOOP_NUM:  program_state = LOOP_NUM;  break;
                    case COUNT_NUM: program_state = COUNT_NUM; break;
                    default:
                    {
                        std::cout << "\n\n--------------ERROR!!!--------------\n"       << std::endl;
                        std::cout << "\tYou made a mistake while entering number!"      << std::endl;
                        std::cout << "\tCould you please enter a number from 1 to 4."   << std::endl;

                        program_state = CHOOSE_A_STATE;
                    }
                    break;
                }
            }
            break;
            case (ENTER_NUM):
            {
                std::cout << "\nPlease, enter your integer number from 0 to 65535:" << std::endl;
                std::cin >> get_number;
                if (selected_loop == true)
                    program_state =  LOOP_NUM;
                else
                {
                    splitNumber_byRank(get_number);
                    program_state = CHOOSE_A_STATE;
                }
            }
            break;
            case (LOOP_NUM): // Displaying number in a loop
            {
                if (!get_number)
                {
                    selected_loop = true;
                    program_state = ENTER_NUM;
                    break;
                }
                int counter = LOOPS;
                std::cout << "\n\nOutput number in loop start here: " << std::endl;
                do
                {
                    splitNumber_byRank(get_number);
                    counter--;
                }
                while (counter);
                std::cout << "\nThere's the end output number in loop. \n\n" << std::endl;
                selected_loop = false;
                program_state = COUNT_NUM;
            }
            break;
        case (COUNT_NUM): // Outputting counter from 0 to 500
            {
                while (cnt_number < numBufferMax)
                {
                    splitNumber_byRank(cnt_number);
                    cnt_number++;
                }
                program_state = ENTER_NUM;
                cnt_number = 0;
            }
            break;
        default:
                program_state = ENTER_NUM;
            break;
        };
    }


    int decimal = 0;
    int binary  = 0;
    // CONVERT DECIMAL NUMBER TO BINARY BY FUNCTION (CLASS-FREE) BEGIN //
    std::cout << "Enter your decimal number: "   << std::endl;
    std::cin  >> decimal;
    std::cout << printBin(decimal)               << std::endl;
    // CONVERT DECIMAL NUMBER TO BINARY BY FUNCTION (CLASS-FREE) END   //

    // CONVERTER BINARY NUMBER TO DECIMAL AND VICE VERSA BEGIN //
    std::cout << "Enter your a decimal number:"  << std::endl;
    std::cin  >> decimal;
    std::cout << dec_to_bin(decimal)             << std::endl;
    // ------------------------------------------------------- //
    std::cout << "\nEnter your a binary number:" << std::endl;
    std::cin  >> binary;
    std::cout << bin_to_dec(binary)              << std::endl;
    // CONVERTER BINARY NUMBER TO DECIMAL AND VICE VERSA END   //

    return 0;
}
