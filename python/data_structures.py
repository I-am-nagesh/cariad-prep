"""
python datat structures 

1  LIST [] -> dynamic array (changeable, ordered, duplicate OK)
2  TUPLE () -> fixed array (unchangeable, ordered, duplicate OK)
3  SET {} -> unordered collection of unique items (changeable, unordered, duplicate NOT OK)
4  DICTIONARY {} -> key-value pairs (changeable, ordered keys, duplicate NOT OK for keys)
"""


def explore_lists():
    print("----1  Lists, like vector in cpp ----")

    cars = ["BMW", "Audi", "Toyota"]

    cars.append("Honda")  # add item to the end

    cars.insert(1, "Mercedes")  # insert at index 1

    subset = cars[1:3]  # slicing from index 1 to 2

    cars.remove("Toyota")  # remove item by value

    last_car = cars.pop()  # remove and return last item

    print(f"final list: {cars}")
    print(f"sliced subset: {subset}")


def explore_tuples():
    print("----2  Tuples ----")

    gps_loc = (48.13, 11.58)

    lat = gps_loc[0]

    latitude, longitude = gps_loc

    print(f"Lat: {latitude}, Long: {longitude}")


def explore_sets():
    print("----3  Sets ----")

    ids_a = {101, 102, 103, 101}
    ids_b = {103, 104, 105}

    ids_a.add(999)
    ids_a.discard(102)

    common = ids_a.intersection(ids_b)
    all_ids = ids_a.union(ids_b)

    print(f"unique set A: {ids_a}")
    print(f"common IDs: {common}")


def explore_dicts():
    print("---4  Dictionaries ---")

    ecu = {
        "id": "0x1A",
        "status": "OK",
        "speed": 0
    }
    print(f"ECU status: {ecu['status']}")

    ecu["temp"] = 85
    ecu["speed"] = 120

    volts = ecu.get("voltage", "N/A")

    print(f"updated ECU: {ecu}")
    print(f"voltage read: {volts}")

    print("iterating: ")
    for key, val in ecu.items():
        print(f" {key} -> {val}")

if __name__ == "__main__":
    explore_lists()
    explore_tuples()
    explore_sets()
    explore_dicts()