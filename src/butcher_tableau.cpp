#include "rk/pch.hpp"
#include "rk/butcher_tableau.hpp"

namespace rk
{
template <typename T>
butcher_tableau<T>::butcher_tableau(const std::vector<T> &alpha, const std::vector<std::vector<T>> &beta,
                                    const std::vector<T> &coefs, const std::uint32_t stages, const std::uint32_t order)
    : alpha(alpha), coefs1(coefs), beta(beta), embedded(false), stages(stages), order(order)
{
}

template <typename T>
butcher_tableau<T>::butcher_tableau(const std::vector<T> &alpha, const std::vector<std::vector<T>> &beta,
                                    const std::vector<T> &coefs1, const std::vector<T> &coefs2,
                                    const std::uint32_t stages, const std::uint32_t order)
    : alpha(alpha), coefs1(coefs1), coefs2(coefs2), beta(beta), embedded(true), stages(stages), order(order)
{
}

template <typename T> const butcher_tableau<T> butcher_tableau<T>::rk1 = {{}, {}, {1.f}, 1, 1};
template <typename T> const butcher_tableau<T> butcher_tableau<T>::rk2 = {{1.f}, {{1.f}}, {0.5f, 0.5f}, 2, 2};
template <typename T>
const butcher_tableau<T> butcher_tableau<T>::rk4 = {
    {0.5f, 0.5f, 1.f}, {{0.5f}, {0.f, 0.5f}, {0.f, 0.f, 1.f}}, {1.f / 6.f, 1.f / 3.f, 1.f / 3.f, 1.f / 6.f}, 4, 4};

template <typename T>
const butcher_tableau<T> butcher_tableau<T>::rk38 = {{1.f / 3.f, 2.f / 3.f, 1.f},
                                                     {
                                                         {1.f / 3.f},
                                                         {-1.f / 3.f, 1.f},
                                                         {1.f, -1.f, 1.f},
                                                     },
                                                     {1.f / 8.f, 3.f / 8.f, 3.f / 8.f, 1.f / 8.f},
                                                     4,
                                                     4};

template <typename T> const butcher_tableau<T> butcher_tableau<T>::rkf12 = {{1}, {{1}}, {0.5f, 0.5f}, {1.f, 0.f}, 2, 2};

template <typename T>
const butcher_tableau<T> butcher_tableau<T>::rkf45 = {
    {0.25f, 3.f / 8.f, 12.f / 13.f, 1.f, 0.5f},
    {{0.25f},
     {3.f / 32.f, 9.f / 32.f},
     {1932.f / 2197.f, -7200.f / 2197.f, 7296.f / 2197.f},
     {439.f / 216.f, -8.f, 3680.f / 513.f, -845.f / 4104.f},
     {-8.f / 27.f, 2.f, -3544.f / 2565.f, 1859.f / 4104.f, -11.f / 40.f}},
    {16.f / 135.f, 0.f, 6656 / 12825.f, 28561.f / 56430.f, -9.f / 50.f, 2.f / 55.f},
    {25.f / 216.f, 0.f, 1408.f / 2565.f, 2197.f / 4104.f, -0.2f, 0.f},
    6,
    5};

template <typename T>
const butcher_tableau<T> butcher_tableau<T>::rkfck45 = {
    {0.2f, 0.3f, 0.6f, 1.f, 7.f / 8.f},
    {{0.2f},
     {3.f / 40.f, 9.f / 40.f},
     {0.3f, -0.9f, 6.f / 5.f},
     {-11.f / 54.f, 2.5f, -70.f / 27.f, 35.f / 27.f},
     {1631.f / 55296.f, 175.f / 512.f, 575.f / 13824.f, 44275.f / 110592.f, 253.f / 4096.f}},
    {37.f / 378.f, 0.f, 250.f / 621.f, 125.f / 594.f, 0.f, 512.f / 1771.f},
    {2825.f / 27648.f, 0.f, 18575.f / 48384.f, 13525.f / 55296.f, 277.f / 14336.f, 0.25f},
    6,
    5};

template <typename T>
const butcher_tableau<T> butcher_tableau<T>::rkf78 = {
    {2.f / 27.f, 1.f / 9.f, 1.f / 6.f, 5.f / 12.f, 0.5f, 5.f / 6.f, 1.f / 6.f, 2.f / 3.f, 1.f / 3.f, 1.f, 0.f, 1.f},
    {{2.f / 27.f},
     {1.f / 36.f, 1.f / 12.f},
     {1.f / 24.f, 0.f, 1.f / 8.f},
     {5.f / 12.f, 0.f, -25.f / 16.f, 25.f / 16.f},
     {1.f / 20.f, 0.f, 0.f, 0.25f, 0.2f},
     {-25.f / 108.f, 0.f, 0.f, 125.f / 108.f, -65.f / 27.f, 125.f / 54.f},
     {31.f / 300.f, 0.f, 0.f, 0.f, 61.f / 225.f, -2.f / 9.f, 13.f / 900.f},
     {2.f, 0.f, 0.f, -53.f / 6.f, 704.f / 45.f, -107.f / 9.f, 67.f / 90.f, 3.f},
     {-91.f / 108.f, 0.f, 0.f, 23.f / 108.f, -976.f / 135.f, 311.f / 54.f, -19.f / 60.f, 17.f / 6.f, -1.f / 12.f},
     {2383.f / 4100.f, 0.f, 0.f, -341.f / 164.f, 4496.f / 1025.f, -301.f / 82.f, 2133.f / 4100.f, 45.f / 82.f,
      45.f / 164.f, 18.f / 41.f},
     {3.f / 205.f, 0.f, 0.f, 0.f, 0.f, -6.f / 41.f, -3.f / 205.f, -3.f / 41.f, 3.f / 41.f, 6.f / 41.f, 0.f},
     {-1777.f / 4100.f, 0.f, 0.f, -341.f / 164.f, 4496.f / 1025.f, -289.f / 82.f, 2193.f / 4100.f, 51.f / 82.f,
      33.f / 164.f, 12.f / 41.f, 0.f, 1.f}},
    {0.f, 0.f, 0.f, 0.f, 0.f, 34.f / 105.f, 9.f / 35.f, 9.f / 35.f, 9.f / 280.f, 9.f / 280.f, 0.f, 41.f / 840.f,
     41.f / 840.f},
    {41.f / 840.f, 0.f, 0.f, 0.f, 0.f, 34.f / 105.f, 9.f / 35.f, 9.f / 35.f, 9.f / 280.f, 9.f / 280.f, 41.f / 840.f,
     0.f, 0.f},
    13,
    8};

#ifdef KIT_USE_YAML_CPP
template <typename T> YAML::Node butcher_tableau<T>::serializer::encode(const butcher_tableau<T> &tb) const
{
    YAML::Node node;
    node["Alpha"] = tb.alpha;
    node[tb.embedded ? "Coefs1" : "Coefs"] = tb.coefs1;
    if (tb.embedded)
        node["Coefs2"] = tb.coefs2;

    for (auto it = node.begin(); it != node.end(); ++it)
        it->second.SetStyle(YAML::EmitterStyle::Flow);

    for (std::size_t i = 0; i < tb.beta.size(); i++)
    {
        YAML::Node child;
        child = tb.beta[i];
        node["Beta"].push_back(child);
        node["Beta"][i].SetStyle(YAML::EmitterStyle::Flow);
    }
    node["Stage"] = tb.stages;
    node["Order"] = tb.order;

    return node;
}
template <typename T> bool butcher_tableau<T>::serializer::decode(const YAML::Node &node, butcher_tableau<T> &tb) const
{
    if (!node.IsMap() || (node.size() < 4 && node.size() > 6))
        return false;

    std::vector<T> alpha, coefs1, coefs2;
    std::vector<std::vector<T>> beta;
    if (node["Beta"])
        for (const auto &n1 : node["Beta"])
        {
            auto &v1 = beta.emplace_back();
            for (const auto &n2 : n1)
                v1.push_back(n2.as<T>());
        }
    for (const auto &n : node["Alpha"])
        alpha.push_back(n.as<T>());

    if (node["Coefs2"])
    {
        for (const auto &n : node["Coefs1"])
            coefs1.push_back(n.as<T>());
        for (const auto &n : node["Coefs2"])
            coefs2.push_back(n.as<T>());
        tb = {alpha, beta, coefs1, coefs2, node["Stage"].as<std::uint32_t>(), node["Order"].as<std::uint32_t>()};
        return true;
    }
    else
        for (const auto &n : node["Coefs"])
            coefs1.push_back(n.as<T>());
    tb = {alpha, beta, coefs1, node["Stage"].as<std::uint32_t>(), node["Order"].as<std::uint32_t>()};
    return true;
}
#endif

template struct butcher_tableau<float>;
template struct butcher_tableau<double>;
template struct butcher_tableau<long double>;
} // namespace rk
