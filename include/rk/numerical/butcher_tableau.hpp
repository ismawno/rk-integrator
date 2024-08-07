#pragma once

#include "kit/utility/type_constraints.hpp"
#include "kit/container/dynarray.hpp"
#include <cstdint>

#ifndef RK_TABLEAU_CAPACITY
#define RK_TABLEAU_CAPACITY 16
#endif

namespace rk
{
template <std::floating_point Float> struct butcher_tableau
{
    using array1 = kit::dynarray<Float, RK_TABLEAU_CAPACITY>;
    using array2 = kit::dynarray<array1, RK_TABLEAU_CAPACITY>;

    butcher_tableau() = default;
    butcher_tableau(const array1 &alpha, const array2 &beta, const array1 &coefs, std::uint32_t stages,
                    std::uint32_t order);

    butcher_tableau(const array1 &alpha, const array2 &beta, const array1 &coefs1, const array1 &coefs2,
                    std::uint32_t stages, std::uint32_t order);

    array1 alpha;
    array1 coefs1;
    array1 coefs2;
    array2 beta;

    bool embedded;
    std::uint32_t stages;
    std::uint32_t order;

    static const butcher_tableau rk1;
    static const butcher_tableau rk2;
    static const butcher_tableau rk4;
    static const butcher_tableau rk38;
    static const butcher_tableau rkf12;
    static const butcher_tableau rkf45;
    static const butcher_tableau rkfck45;
    static const butcher_tableau rkf78;
};

template <std::floating_point Float> const butcher_tableau<Float> butcher_tableau<Float>::rk1 = {{}, {}, {1.f}, 1, 1};
template <std::floating_point Float>
const butcher_tableau<Float> butcher_tableau<Float>::rk2 = {{1.f}, {{1.f}}, {0.5f, 0.5f}, 2, 2};
template <std::floating_point Float>
const butcher_tableau<Float> butcher_tableau<Float>::rk4 = {
    {0.5f, 0.5f, 1.f}, {{0.5f}, {0.f, 0.5f}, {0.f, 0.f, 1.f}}, {1.f / 6.f, 1.f / 3.f, 1.f / 3.f, 1.f / 6.f}, 4, 4};

template <std::floating_point Float>
const butcher_tableau<Float> butcher_tableau<Float>::rk38 = {{1.f / 3.f, 2.f / 3.f, 1.f},
                                                             {
                                                                 {1.f / 3.f},
                                                                 {-1.f / 3.f, 1.f},
                                                                 {1.f, -1.f, 1.f},
                                                             },
                                                             {1.f / 8.f, 3.f / 8.f, 3.f / 8.f, 1.f / 8.f},
                                                             4,
                                                             4};

template <std::floating_point Float>
const butcher_tableau<Float> butcher_tableau<Float>::rkf12 = {{1}, {{1}}, {0.5f, 0.5f}, {1.f, 0.f}, 2, 2};

template <std::floating_point Float>
const butcher_tableau<Float> butcher_tableau<Float>::rkf45 = {
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

template <std::floating_point Float>
const butcher_tableau<Float> butcher_tableau<Float>::rkfck45 = {
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

template <std::floating_point Float>
const butcher_tableau<Float> butcher_tableau<Float>::rkf78 = {
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
} // namespace rk
