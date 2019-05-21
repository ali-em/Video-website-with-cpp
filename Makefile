CC := g++
CFLAGS := -std=c++11 
TO_O_FLAG := -c

OC := $(CC) $(CFLAGS) $(TO_O_FLAG)
COMPILE := $(CC) $(CFLAGS)

BUILD = build

# MODELS
USER_MODEL := models/user.h
PUBLISHER_MODEL := models/publisher.h
FILM := models/film.h
NOTIF := models/notification.h
COMMENT := models/comment.h
PURCHASE := models/purchase.h
REQUEST_TYPE := models/request_type.h
ALL_MODELS := $(REQUEST_TYPE) $(USER_MODEL) $(PUBLISHER_MODEL) $(FILM) $(NOTIF) $(COMMENT) $(PURCHASE)

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


all:$(BUILD) app.out

$(BUILD):
	mkdir -p $(BUILD) 

$(BUILD)/main.o:main.cpp $(BUILD)/app.o
	$(OC) main.cpp -o $(BUILD)/main.o

$(BUILD)/app.o:$(APP).h $(APP).cpp $(BUILD)/database.o $(BUILD)/input_handler.o $(BUILD)/view.o $(BUILD)/tools.o $(BUILD)/login.o $(BUILD)/signup.o $(BUILD)/film_manager.o $(BUILD)/follower_handler.o $(BUILD)/money_handler.o $(BUILD)/comment_handler.o $(BUILD)/notification_handler.o
	$(OC) $(APP).cpp -o $(BUILD)/app.o

$(BUILD)/database.o:$(BUILD)/user.o $(BUILD)/publisher.o $(DATABASE).cpp $(DATABASE).h $(ALL_MODELS) $(BUILD)/film_manager.o $(BUILD)/film.o
	$(OC) $(DATABASE).cpp -o $(BUILD)/database.o

$(BUILD)/input_handler.o: $(INPUT).cpp $(INPUT).h $(ALL_MODELS)
	$(OC) $(INPUT).cpp -o $(BUILD)/input_handler.o

$(BUILD)/view.o:$(VIEW).h $(VIEW).cpp $(ALL_MODELS)
	$(OC) $(VIEW).cpp -o $(BUILD)/view.o

$(BUILD)/publisher.o:$(PUBLISHER_MODEL) $(PUB_CPP) $(USER_MODEL)
	$(OC) $(PUB_CPP) -o $(BUILD)/publisher.o

$(BUILD)/user.o:$(USER_CPP) $(USER_MODEL)
	$(OC) $(USER_CPP) -o $(BUILD)/user.o

$(BUILD)/signup.o:$(SIGN_UP).h $(SIGN_UP).cpp $(BUILD)/login.o
	$(OC) $(SIGN_UP).cpp -o $(BUILD)/signup.o

$(BUILD)/login.o:$(LOGIN).h $(LOGIN).cpp $(TOOLS).h
	$(OC) $(LOGIN).cpp -o $(BUILD)/login.o

$(BUILD)/tools.o:$(TOOLS).h $(TOOLS).cpp 
	$(OC) $(TOOLS).cpp -o $(BUILD)/tools.o

$(BUILD)/film.o:$(FILM_CPP) $(ALL_MODELS) $(BUILD)/purchase.o $(BUILD)/comment.o
	$(OC) $(FILM_CPP) -o $(BUILD)/film.o
	
$(BUILD)/comment.o:$(COMMENT_CPP) $(ALL_MODELS) 
	$(OC) $(COMMENT_CPP) -o $(BUILD)/comment.o

$(BUILD)/film_manager.o:$(FILM_MANAGER).h $(FILM_MANAGER).cpp $(TOOLS).h $(FILM)
	$(OC) $(FILM_MANAGER).cpp -o $(BUILD)/film_manager.o
	
$(BUILD)/follower_handler.o:$(FOLLOWER).h $(FOLLOWER).cpp $(TOOLS).h
	$(OC) $(FOLLOWER).cpp -o $(BUILD)/follower_handler.o

$(BUILD)/notification_handler.o:$(NOTIF_HANDLER).h $(NOTIF_HANDLER).cpp $(TOOLS).h $(BUILD)/notification.o
	$(OC) $(NOTIF_HANDLER).cpp -o $(BUILD)/notification_handler.o

$(BUILD)/money_handler.o:$(MONEY).h $(MONEY).cpp $(BUILD)/tools.o $(BUILD)/film.o
	$(OC) $(MONEY).cpp -o $(BUILD)/money_handler.o

$(BUILD)/purchase.o:$(PURCHASE_CPP) $(PURCHASE)
	$(OC) $(PURCHASE_CPP) -o $(BUILD)/purchase.o

$(BUILD)/notification.o:$(NOTIF) $(NOTIF_CPP)
	$(OC) $(NOTIF_CPP) -o $(BUILD)/notification.o

$(BUILD)/comment_handler.o:$(COMMENT_HANDLER).h $(COMMENT_HANDLER).cpp $(BUILD)/tools.o
	$(OC) $(COMMENT_HANDLER).cpp -o $(BUILD)/comment_handler.o

app.out:$(BUILD)/main.o
	$(COMPILE) $(BUILD)/app.o $(BUILD)/main.o $(BUILD)/purchase.o $(BUILD)/database.o $(BUILD)/input_handler.o $(BUILD)/view.o $(BUILD)/publisher.o $(BUILD)/user.o $(BUILD)/signup.o $(BUILD)/login.o $(BUILD)/tools.o $(BUILD)/film.o $(BUILD)/comment.o $(BUILD)/film_manager.o $(BUILD)/follower_handler.o $(BUILD)/notification_handler.o $(BUILD)/money_handler.o $(BUILD)/notification.o $(BUILD)/comment_handler.o  -o app.out


.PHONY: clean

clean:
	rm -rf $(BUILD) *.o app.out
