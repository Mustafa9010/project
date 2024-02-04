def henon_map(x, y, a=1.4, b=0.3):
    new_x = 1 - a * x**2 + y
    new_y = b * x
    return new_x, new_y

def construct_s_box(KS, rounds, omega):
    xS, yS = KS
    s_box = list(range(256))  # Initialize with identity mapping
    rt = s_box[:rounds]

    # Generate S-box values using Henon map
    for i in range(256):
        xS, yS = henon_map(xS, yS)
        index = int((xS * 1000) % 256)
        s_box[i], s_box[index] = s_box[index], s_box[i]

    return [hex(val) for val in s_box]

# Example usage
KS = (0.1, 0.2)  # Initial values for Henon map
rounds = 100  # Example number of rounds
omega = 3  # Example value for omega
s_box = construct_s_box(KS, rounds, omega)
print("Constructed S-box:", s_box)

