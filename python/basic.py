car_model = "Audi"
speed = 120
print(f"the {car_model} is going at {speed} km/h")

battery_level = 75

if battery_level == 100:
    print("fully charged")
elif battery_level> 20:
    print("battery ok")
else:
    print("low battery!")
    print("please charge soon")


for i in range(5):
    print(f"checking sensor {i}")

sensors = ["lidar", "camera", "ultrasonic", "radar"]

for s in sensors:
    print(f"I have a {s} sensor")


count = 0
while count < 3:
    print("waiting...")
    count = count + 1


def check_speed_limit(current_speed):
    limit = 100
    if current_speed > limit:
        return False
    else:
        return True
    

my_speed = 110
is_safe = check_speed_limit(my_speed)

if is_safe:
    print("safe driving")

else:
    print("overspeeding!")



def suggest_gear(speed, is_sport_mode):
    if speed == 0:
        return "N"
    
    if is_sport_mode:
        if speed <= 40:
            return "1"
        else:
            return "2"
        
    else:
        if speed <= 30:
            return "1"
        else:
            return "2"


print(f"sport mode (35kmph): {suggest_gear(35, True)}")
print(f"eco mode (35kmph): {suggest_gear(35, False)}")


readings = [12, 15, -1, 14, -1, 10]

total_value = 0
valid_count = 0

for val in readings:
    if val == -1:
        continue
    total_value += val
    valid_count += 1

print(f"sum of valid sensors: {total_value}")
print(f"count of valid sensors: {valid_count}")



def calc_efficiency(distance_km, fuel_liters):
    if fuel_liters == 0:
        return 0.0
    
    result = distance_km / fuel_liters
    return result

for i in range(3):
    print(f"\n--- calculations {i+1} ---")

    try:
        dist = float(input("enter distance (km): "))
        fuel = float(input("enter fuel (litrers): "))

        efficiency = calc_efficiency(dist, fuel)
        print(f"efficiency: {efficiency: .2f} km/l")

    except ValueError:
        print("error: please enter numbers only!")