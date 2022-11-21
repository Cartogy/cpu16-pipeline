
template <typename T, typename U>
class ControlUnit {
    public:
        virtual U control_op(T ins) const = 0;
};
