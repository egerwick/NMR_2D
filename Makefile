CXX = g++

SOURCES = Main.C HSQC_Data.C 
OBJS = $(SOURCES:.cpp=.o)

CXXFLAGS = -I. -I/opt/local/include \
            -std=c++11 -stdlib=libc++ \
            -g3 -Wall -O0

LDFLAGS = -L/usr/lib $(pkg-config --libs --cflags opencv) -lm -ljpeg
LDFLAGS = -L/usr/lib -I/opt/local/include/opencv -I/opt/local/include -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lm -ljpeg

.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $^

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o SIM_ALG $(OBJS)

clean:
	rm -rf *.o
