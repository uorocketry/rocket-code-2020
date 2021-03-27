with open("fixed.txt", "w") as output_file:
    with open("input.txt") as input_file:
        cols = 0

        while True:
            vals = input_file.read(1)

            if not vals:
                break

            if cols == 24:
                if vals == ",":
                    output_file.write("0,")
                else:
                    s = bytes(vals, encoding='ascii')
                    i = int.from_bytes(s, "little")
                    output_file.write(str(i))

                cols += 1
                continue

            output_file.write(vals)

            if vals == ",":
                cols += 1
            elif vals == "\n":
                cols = 0
