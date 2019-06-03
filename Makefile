CC := g++
CFLAGS := -std=c++11  -g
TO_O_FLAG := -c

OC := $(CC) $(CFLAGS) $(TO_O_FLAG)
COMPILE := $(CC) $(CFLAGS)
TEMPLATE_DIR=.template

BUILD = build

# MODELS
USER_MODEL := server/models/user.h
PUBLISHER_MODEL := server/models/publisher.h
FILM := server/models/film.h
NOTIF := server/models/notification.h
COMMENT := server/models/comment.h
PURCHASE := server/models/purchase.h
REQUEST_TYPE := server/models/request_type.h
ALL_MODELS := $(REQUEST_TYPE) $(USER_MODEL) $(PUBLISHER_MODEL) $(FILM) $(NOTIF) $(COMMENT) $(PURCHASE)

USER_CPP := server/models/user.cpp
PUB_CPP := server/models/publisher.cpp
FILM_CPP := server/models/film.cpp
PURCHASE_CPP := server/models/purchase.cpp
COMMENT_CPP := server/models/comment.cpp
NOTIF_CPP := server/models/notification.cpp

#views
VIEW := server/views/view
DATABASE := server/database/database


#controllers
APP := server/controllers/app
INPUT := server/controllers/input_handler
LOGIN := server/controllers/login
SIGN_UP := server/controllers/signup
TOOLS := server/controllers/tools
FILM_MANAGER := server/controllers/film_manager
FOLLOWER := server/controllers/follower_handler
MONEY := server/controllers/money_handler
COMMENT_HANDLER := server/controllers/comment_handler
NOTIF_HANDLER := server/controllers/notification_handler
RECOMMENDATION := server/controllers/recommendation_system

#others

MAIN = server/main.cpp
MY_SERVER = server/my_server
MIDDLEWARE = server/controllers/handleRequest
HANDLERS = server/controllers/handlers

all:$(BUILD) app.out

app.out:$(BUILD)/main.o $(BUILD)/response.o $(BUILD)/request.o $(BUILD)/utilities.o $(BUILD)/server.o $(BUILD)/route.o $(BUILD)/template_parser.o $(BUILD)/my_server.o $(BUILD)/middleware.o $(BUILD)/handlers.o
	$(COMPILE)  $(BUILD)/app.o $(BUILD)/recommendation_system.o $(BUILD)/main.o $(BUILD)/purchase.o $(BUILD)/database.o $(BUILD)/input_handler.o $(BUILD)/view.o $(BUILD)/publisher.o $(BUILD)/user.o $(BUILD)/signup.o $(BUILD)/login.o $(BUILD)/tools.o $(BUILD)/film.o $(BUILD)/comment.o $(BUILD)/film_manager.o $(BUILD)/follower_handler.o $(BUILD)/notification_handler.o $(BUILD)/money_handler.o $(BUILD)/notification.o $(BUILD)/comment_handler.o $(BUILD)/response.o $(BUILD)/request.o $(BUILD)/utilities.o $(BUILD)/server.o $(BUILD)/route.o $(BUILD)/template_parser.o $(BUILD)/my_server.o $(BUILD)/middleware.o $(BUILD)/handlers.o -o app.out


$(BUILD):
	mkdir -p $(BUILD) 

$(BUILD)/main.o:$(MAIN) $(BUILD)/app.o
	$(OC) $(MAIN) -o $(BUILD)/main.o

$(BUILD)/app.o:$(APP).h $(APP).cpp $(BUILD)/database.o $(BUILD)/input_handler.o $(BUILD)/view.o $(BUILD)/tools.o $(BUILD)/login.o $(BUILD)/signup.o $(BUILD)/film_manager.o $(BUILD)/follower_handler.o $(BUILD)/money_handler.o $(BUILD)/comment_handler.o $(BUILD)/notification_handler.o $(BUILD)/recommendation_system.o 
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

$(BUILD)/film_manager.o:$(FILM_MANAGER).h $(FILM_MANAGER).cpp $(TOOLS).h $(FILM) $(BUILD)/recommendation_system.o
	$(OC) $(FILM_MANAGER).cpp -o $(BUILD)/film_manager.o
	
$(BUILD)/follower_handler.o:$(FOLLOWER).h $(FOLLOWER).cpp $(TOOLS).h
	$(OC) $(FOLLOWER).cpp -o $(BUILD)/follower_handler.o

$(BUILD)/notification_handler.o:$(NOTIF_HANDLER).h $(NOTIF_HANDLER).cpp $(TOOLS).h $(BUILD)/notification.o
	$(OC) $(NOTIF_HANDLER).cpp -o $(BUILD)/notification_handler.o

$(BUILD)/money_handler.o:$(MONEY).h $(MONEY).cpp $(BUILD)/tools.o $(BUILD)/film.o $(BUILD)/recommendation_system.o
	$(OC) $(MONEY).cpp -o $(BUILD)/money_handler.o

$(BUILD)/purchase.o:$(PURCHASE_CPP) $(PURCHASE)
	$(OC) $(PURCHASE_CPP) -o $(BUILD)/purchase.o

$(BUILD)/notification.o:$(NOTIF) $(NOTIF_CPP)
	$(OC) $(NOTIF_CPP) -o $(BUILD)/notification.o

$(BUILD)/comment_handler.o:$(COMMENT_HANDLER).h $(COMMENT_HANDLER).cpp $(BUILD)/tools.o
	$(OC) $(COMMENT_HANDLER).cpp -o $(BUILD)/comment_handler.o

$(BUILD)/recommendation_system.o:$(RECOMMENDATION).h $(RECOMMENDATION).cpp $(BUILD)/tools.o
	$(OC) $(RECOMMENDATION).cpp -o $(BUILD)/recommendation_system.o

#------------------------------------------------------------------------------

$(BUILD)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(OC) utils/template_parser.cpp -o $(BUILD)/template_parser.o

$(BUILD)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(OC) utils/response.cpp -o $(BUILD)/response.o

$(BUILD)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(OC) utils/request.cpp -o $(BUILD)/request.o

$(BUILD)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(OC) utils/utilities.cpp -o $(BUILD)/utilities.o

$(BUILD)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(OC) server/server.cpp -o $(BUILD)/server.o

$(BUILD)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(OC) server/route.cpp -o $(BUILD)/route.o

$(BUILD)/my_server.o: $(MY_SERVER).cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(OC) $(MY_SERVER).cpp -o $(BUILD)/my_server.o


$(BUILD)/middleware.o:$(MIDDLEWARE).h $(MIDDLEWARE).cpp $(BUILD)/tools.o
	$(OC) $(MIDDLEWARE).cpp -o $(BUILD)/middleware.o


$(BUILD)/handlers.o:$(HANDLERS).h $(HANDLERS).cpp $(BUILD)/tools.o $(APP).h
	$(OC) $(HANDLERS).cpp -o $(BUILD)/handlers.o

.PHONY: clean

clean:
	rm -rf $(BUILD) *.o app.out
