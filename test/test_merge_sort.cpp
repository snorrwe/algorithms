#include "merge_sort.hpp"
#include "gtest/gtest.h"
#include <vector>

namespace {

template <typename T>
void expect_ordered(T const& v)
{
    auto begin = v.begin();
    auto next = begin + 1;

    for (; next != v.end(); ++begin, ++next) {
        EXPECT_LE(*begin, *next);
    }
}

TEST(MergeSort, Easy)
{
    std::vector v { 2, 1, 3 };
    merge_sort::sort(v.begin(), v.end());

    expect_ordered(v);
}

TEST(MergeSort, AlreadySorted)
{
    std::vector v { 1, 2, 3 };
    merge_sort::sort(v.begin(), v.end());

    expect_ordered(v);
}

TEST(MergeSort, InReverseOrder)
{
    std::vector v { 3, 2, 1 };
    merge_sort::sort(v.begin(), v.end());

    expect_ordered(v);
}

TEST(MergeSort, SingleItem)
{
    std::vector v { 1 };
    merge_sort::sort(v.begin(), v.end());

    expect_ordered(v);
}

TEST(MergeSort, HomogenousRange)
{
    std::vector v { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    merge_sort::sort(v.begin(), v.end());

    expect_ordered(v);
}

TEST(MergeSort, LongRandoms)
{
    std::vector v {
        629, 887, 275, 967, 727, 303, 942, 586, 522, 327, 315, 587, 219, 724,
        460, 834, 540, 890, 719, 830, 796, 428, 696, 953, 194, 693, 441, 493,
        237, 901, 338, 984, 700, 316, 329, 767, 548, 591, 984, 752, 295, 518,
        172, 264, 539, 212, 166, 180, 841, 645, 775, 848, 742, 416, 919, 823,
        454, 309, 476, 590, 254, 125, 696, 966, 699, 923, 510, 269, 712, 142,
        665, 481, 220, 322, 623, 973, 588, 416, 352, 828, 230, 964, 595, 336,
        190, 607, 993, 666, 528, 301, 245, 484, 990, 822, 416, 905, 326, 263,
        664, 130, 316, 666, 322, 660, 675, 907, 768, 196, 435, 517, 413, 902,
        413, 357, 375, 673, 154, 178, 589, 505, 703, 147, 316, 435, 810, 251,
        118, 694, 323, 379, 372, 298, 396, 877, 109, 699, 386, 577, 720, 796,
        584, 862, 662, 133, 783, 692, 210, 672, 977, 553, 638, 934, 820, 203,
        472, 257, 708, 521, 383, 811, 917, 663, 645, 254, 673, 690, 801, 556,
        288, 827, 455, 112, 887, 277, 577, 640, 847, 133, 531, 955, 888, 840,
        596, 635, 500, 940, 601, 301, 880, 350, 721, 977, 711, 291, 801, 643,
        110, 753, 828, 233, 612, 160, 115, 202, 286, 114, 628, 281, 761, 616,
        512, 781, 838, 295, 955, 304, 907, 217, 532, 741, 771, 976, 263, 884,
        403, 384, 809, 895, 682, 174, 766, 596, 240, 857, 717, 730, 914, 219,
        749, 652, 753, 158, 405, 917, 851, 692, 417, 548, 610, 560, 122, 842,
        222, 934, 966, 188, 642, 816, 755, 621, 278, 475, 895, 935, 530, 552,
        965, 302, 244, 190, 365, 231, 848, 957, 285, 637, 944, 956, 189, 469,
        549, 523, 380, 195, 300, 720, 558, 325, 695, 425, 306, 806, 419, 557,
        925, 692, 733, 607, 685, 667, 258, 872, 992, 105, 153, 164, 254, 369,
        987, 592, 337, 307, 747, 983, 708, 895, 232, 231, 569, 279, 603, 505,
        976, 809, 157, 625, 610, 128, 985, 434, 198, 876, 196, 756, 501, 742,
        300, 663, 359, 584, 991, 925, 272, 726, 617, 593, 710, 299, 523, 412,
        753, 201, 502, 102, 707, 495, 497, 809, 298, 736, 719, 214, 434, 489,
        852, 758, 967, 743, 770, 786, 139, 275, 827, 621, 224, 417, 850, 641,
        691, 636, 588, 360, 314, 998, 957, 952, 662, 377, 986, 124, 483, 524,
        256, 360, 656, 515, 411, 557, 475, 465, 810, 763, 366, 405, 267, 403,
        732, 871, 969, 847, 901, 659, 148, 181, 870, 456, 123, 904, 549, 709,
        382, 557, 992, 325, 333, 287, 724, 859, 524, 391, 119, 390, 928, 304,
        388, 529, 974, 938, 929, 585, 556, 331, 309, 530, 989, 235, 639, 736,
        940, 754, 553, 735, 941, 419, 594, 545, 160, 166, 476, 549, 711, 915,
        639, 430, 450, 149, 750, 867, 451, 209, 264, 900, 640, 646, 750, 258,
        261, 461, 712, 891, 744, 387, 662, 365, 336, 736, 256, 699, 884, 668,
        412, 627, 504, 208, 813, 898, 889, 880, 838, 700, 470, 156, 757, 700,
        551, 764, 191, 498, 525, 221, 157, 254, 992, 581

    };
    merge_sort::sort(v.begin(), v.end());

    expect_ordered(v);
}

TEST(MergeSort, CustomType)
{
    struct MyType {
        int value;

        bool operator<=(MyType const& other) const
        {
            return value <= other.value;
        }
    };

    std::vector v {
        MyType { 1 },
        MyType { 551 },
        MyType { 764 },
        MyType { 191 },
        MyType { 498 },
        MyType { 525 },
        MyType { 221 },
        MyType { 157 },
        MyType { 254 },
        MyType { 992 },
        MyType { 581 },
    };

    merge_sort::sort(v.begin(), v.end());

    expect_ordered(v);
}
} // namespace

