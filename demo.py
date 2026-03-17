from pypolypart import optimal_convex_partition_2


def main() -> None:
    polygon = [
        (391, 374),
        (240, 431),
        (252, 340),
        (374, 320),
        (289, 214),
        (134, 390),
        (68, 186),
        (154, 259),
        (161, 107),
        (435, 108),
        (208, 148),
        (295, 160),
        (421, 212),
        (441, 303),
    ]

    parts = optimal_convex_partition_2(polygon)

    print("Input polygon:")
    print(polygon)
    print()

    print(f"Number of convex pieces: {len(parts)}")
    for idx, poly in enumerate(parts, start=1):
        print(f"Convex part {idx}:")
        for pt in poly:
            print(f"  {pt}")
        print()


if __name__ == "__main__":
    main()