wuwabot_reader, reads Character Profile Image URL generated from wuwa-bot in Discord Channel, 
your character information will be stored in result.json (will be disappear after each upload)

*************************************************************************************************
*************************************************************************************************
To use this: 
  1. Download curl by running:
       sudo apt install libcurl4-openssl-dev
  2. Compile the program in main folder by:
       g++ *.cpp -o NAMEYOUR.EXECUTABLE -lcurl
  3. Run program with or without your Image URL
       ./NAMEYOUR.EXECUTABLE YOUR.URL/of_image
     or if you want error log printed in error.log,
       ./NAMEYOUR.EXECUTABLE YOUR.URL/of_image 2> error.log
  4. To run the program again, just Repeat Step 3

------------------------------------------------------------------------

Check your Result: 
  find result.json generated in the same directory as MAIN.cpp

*************************************************************************************************
*************************************************************************************************

DISCLAIMER:

This project implements stb and curl for several core features, their source code are open via
  https://github.com/nothings/stb
  https://curl.se/

This project is created in a fan-based purpose to improve the gaming experience of Wuthering 
Waves. It is not eligible to use in finincial purpose
DO NOT USE THIS PROJECT FOR YOUR FINANCIAL INTEREST

This project will download images from the Internet, and will read & write some files stored 
locally. The creator of the project limits those file access only to the sub-folders in 
./SourceImage. But still, the risk of getting unidentified downloads still exists. Please use
this project at your own risk. 
 
*************************************************************************************************

version 1.0
By Dropkick
Nov 26, 2025