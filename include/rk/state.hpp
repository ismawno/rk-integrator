#pragma once

#include <vector>
#include "kit/interface/serialization.hpp"

namespace rk
{
template <typename T> class state
{
  public:
#ifdef KIT_USE_YAML_CPP
    class serializer : public kit::serializer<state>
    {
      public:
        YAML::Node encode(const state &tb) const override;
        bool decode(const YAML::Node &node, state &tb) const override;
    };
#endif

    state() = default;
    state(const std::vector<T> &vars, std::uint32_t stages);

    void push_back(T elm);
    void append(std::initializer_list<T> lst);

    void resize(std::size_t size);
    void reserve(std::size_t capacity);

    void clear();

    T operator[](std::size_t index) const;
    T &operator[](std::size_t index);

    const std::vector<T> &vars() const;
    void vars(const std::vector<T> &vars);

    std::size_t size() const;

  private:
    void resize_kvec_length();
    void set_stages(std::uint32_t stages);

    std::vector<T> m_vars;
    std::vector<std::vector<T>> m_kvec;

    friend class integrator;
};
} // namespace rk
