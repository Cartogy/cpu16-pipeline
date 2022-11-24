/** Abstract ALU Interface to be derived **/

template <typename T, typename U>
class ALU {
    public:
        virtual T compute(const T v1, const T v2, const U setting) const = 0;
};
