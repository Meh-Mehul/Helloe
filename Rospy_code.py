import inspect
import queue
import rospy, time
from std_msgs.msg import String

rospy.init_node("Sender")
rate = rospy.Rate(1)

pub = rospy.Publisher('chatter', String, queue_size = 10)
def pub_stuff(pubbed: str):
    dataS = String()
    dataS.data = pubbed
    pub.publish(dataS)
    rate.sleep()
while True:
    inp = input("Enter Text to be displayed: ")
    if(len(inp) > 40):
        inp1 = inp[0:38] + "..."
        inp2 = "..." + inp[38::]
        pub_stuff(inp1)
        time.sleep(4)
        pub_stuff(inp2)
        time.sleep(3)
    elif(len(inp) > 65):
        print("Please Give Text Less than 65 characters unit length")
    else:
        pub_stuff(inp)
        time.sleep(2)
