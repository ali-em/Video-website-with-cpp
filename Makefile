CC := g++
CFLAGS := -std=c++11
TO_O_FLAG := -c

OC := ${CC} ${CFLAGS} ${TO_O_FLAG}
COMPILE := ${CC} ${CFLAGS}


# MODELS
USER_MODEL := models/user.h
PUBLISHER_MODEL := models/publisher.h
FILM := models/film.h
NOTIF := models/notification.h
COMMENT := models/comment.h
PURCHASE := models/purchase.h
REQUEST_TYPE := models/request_type.h
ALL_MODELS := ${REQUEST_TYPE} ${USER_MODEL} ${PUBLISHER_MODEL} ${FILM} ${NOTIF} ${COMMENT} ${PURCHASE}

USER_CPP := models/user.cpp
PUB_CPP := models/publisher.cpp


#views
VIEW := views/view
DATABASE := database/database


#controllers
APP := controllers/app
INPUT := controllers/input_handler

#others
MAIN = main.cpp


all:app.out

app.out:main.o
	${COMPILE} *.o -o app.out

main.o:main.cpp app.o
	${OC} main.cpp

app.o:${APP}.h ${APP}.cpp database.o input_handler.o view.o
	${OC} ${APP}.cpp

database.o:user.o publisher.o ${DATABASE}.cpp ${DATABASE}.h ${ALL_MODELS}
	${OC} ${DATABASE}.cpp

input_handler.o: ${INPUT}.cpp ${INPUT}.h ${ALL_MODELS}
	${OC} ${INPUT}.cpp

view.o:${VIEW}.h ${VIEW}.cpp
	${OC} ${VIEW}.cpp

publisher.o:${PUBLISHER_MODEL} ${PUB_CPP} ${USER_MODEL}
	${OC} ${PUB_CPP}

user.o:${USER_CPP} ${USER_MODEL}
	${OC} ${USER_CPP}

.PHONY: clean

clean:
	rm *.o app.out
