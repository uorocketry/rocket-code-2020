with open("fixed.txt", "w") as output_file:

    with open("input.txt") as input_file:
        cols = 0
        read = False

        while True:
            vals = input_file.read(1)
            
            if not vals:
                break

            val = vals[0]

            if cols == 24 and not read:
                s = bytes(vals, encoding='ascii')
                i = int.from_bytes(s, "little")
                output_file.write(str(i))
                read = True
                continue

            output_file.write(val)

            if val == ",":
                cols += 1
            elif val == "\n":
                cols = 0

            read = False
