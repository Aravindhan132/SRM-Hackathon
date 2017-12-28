sudo apt-get update
sudo apt-get upgrade
sudo apt-get install motion
sudo nano /etc/motion/motion.conf
	daemon ON
	framerate 1000 to 1500
	stream_port 8081
	stream_quality 100
	stream_localhost OFF
	webcontrol_localhost OFF
	quality 100
	width 640
	height 480
	post_capture 5
sudo nano /etc/default/motion
	start_motion_deamon yes
sudo service motion restart
sudo motion

@chrome 
http://<ip-rpi>:8081
