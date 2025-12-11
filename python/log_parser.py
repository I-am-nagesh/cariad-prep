"""
reading the file
extract ip address and error and success logs
save the output in csv/excel
send email

"""

# logfile = open("serverlogs.log", "r")

# for log in logfile:
#     print(log)

with open("serverlogs.log", "r") as file:
    for line in file:
        #getting IP address(split by space, take the first part)
        parts = line.split(" ")
        ip_address = parts[0]

        print(f"found IP: {ip_address}")