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