"""
reading the file
extract ip address and error and success logs
save the output in csv/excel
send email

"""

# logfile = open("serverlogs.log", "r")

# for log in logfile:
#     print(log)

# with open("serverlogs.log", "r") as file:
#     for line in file:
#         #getting IP address(split by space, take the first part)
#         parts = line.split(" ")
#         ip_address = parts[0]

#         print(f"found IP: {ip_address}")


with open("serverlogs.log", "r") as file:
    for line in file:
        
        #getting IP
        parts = line.split(" ")
        ip = parts[0]
        
        #split the wholw line by word "requestsuccessful:"
        temp_part = line.split("requestsuccessful:")

        if len(temp_part) > 1:
            remainder = temp_part[1]     # this is 2nd part

            #split the remainder by "requestfailed:"
            numbers = remainder.split("requestfailed:")

            success_count = numbers[0].strip()    #remove extra space
            failed_count = numbers[1].strip()     #remove extra space

            print(f"IP: {ip} | Success: {success_count} | Failed: {failed_count}")


