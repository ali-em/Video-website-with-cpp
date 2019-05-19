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
FILM_CPP := models/film.cpp
PURCHASE_CPP := models/purchase.cpp
COMMENT_CPP := models/comment.cpp
NOTIF_CPP := models/notification.cpp

#views
VIEW := views/view
DATABASE := database/database


#controllers
APP := controllers/app
INPUT := controllers/input_handler
LOGIN := controllers/login
SIGN_UP := controllers/signup
TOOLS := controllers/tools
FILM_MANAGER := controllers/film_manager
FOLLOWER := controllers/follower_handler
MONEY := controllers/money_handler
COMMENT_HANDLER := controllers/comment_handler
NOTIF_HANDLER := controllers/notification_handler
#others
MAIN = main.cpp


all:app.out

app.out:main.o
	${COMPILE} *.o -o app.out

main.o:main.cpp app.o
	${OC} main.cpp

app.o:${APP}.h ${APP}.cpp database.o input_handler.o view.o tools.o login.o signup.o film_manager.o follower_handler.o money_handler.o comment_handler.o
	${OC} ${APP}.cpp

database.o:user.o publisher.o ${DATABASE}.cpp ${DATABASE}.h ${ALL_MODELS} film_manager.o film.o
	${OC} ${DATABASE}.cpp

input_handler.o: ${INPUT}.cpp ${INPUT}.h ${ALL_MODELS}
	${OC} ${INPUT}.cpp

view.o:${VIEW}.h ${VIEW}.cpp
	${OC} ${VIEW}.cpp

publisher.o:${PUBLISHER_MODEL} ${PUB_CPP} ${USER_MODEL}
	${OC} ${PUB_CPP}

user.o:${USER_CPP} ${USER_MODEL}
	${OC} ${USER_CPP}

signup.o:${SIGN_UP}.h ${SIGN_UP}.cpp login.o
	${OC} ${SIGN_UP}.cpp

login.o:${LOGIN}.h ${LOGIN}.cpp ${TOOLS}.h
	${OC} ${LOGIN}.cpp

film.o:${FILM_CPP} ${ALL_MODELS} purchase.o comment.o
	${OC} ${FILM_CPP}
	
comment.o:${COMMENT_CPP} ${ALL_MODELS} 
	${OC} ${COMMENT_CPP}

film_manager.o:${FILM_MANAGER}.h ${FILM_MANAGER}.cpp ${TOOLS}.h
	${OC} ${FILM_MANAGER}.cpp
	
follower_handler.o:${FOLLOWER}.h ${FOLLOWER}.cpp ${TOOLS}.h
	${OC} ${FOLLOWER}.cpp

notification_handler.o:${NOTIF_HANDLER}.h ${NOTIF_HANDLER}.cpp ${TOOLS}.h
	${OC} ${NOTIF_HANDLER}.cpp

money_handler.o:${MONEY}.h ${MONEY}.cpp tools.o film.o
	${OC} ${MONEY}.cpp

purchase.o:${PURCHASE_CPP} ${PURCHASE}
	${OC} ${PURCHASE_CPP}

tools.o:${TOOLS}.h ${TOOLS}.cpp
	${OC} ${TOOLS}.cpp

notif.o:${NOTIF} ${NOTIF_CPP}
	${OC} ${NOTIF_CPP}

comment_handler.o:${COMMENT_HANDLER}.h ${COMMENT_HANDLER}.cpp tools.o
	${OC} ${COMMENT_HANDLER}.cpp


.PHONY: clean

clean:
	rm *.o app.out
