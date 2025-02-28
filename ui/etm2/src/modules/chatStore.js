//Store for chat features


const chatStore = {
   state: () => ({
      isChatOn: false,
      //messages feature, every message include message sender, send time and message, messages number/count get by length
      // messages: [{UUID:"UUID", sessionID:0, sender: 'admin', time: Date.now(), text: 'Messages from the hardware, admin team and collaborators will appear here' }, { sender: 'user', time: Date.now(), text: 'This is the message from user' }],
      messageIndex: null,
      //sessions feature, every session include {username:"UUID1",sessionId:1, topic:"session 1", messages:[], updateAt:Date.now()},sessions number/count get by length
      sessions: [{ id: Date.now(), username: 'this.getLogUUID', topic: "session", messages: [{ sender: "system", time: new Date().getTime(), text: 'This is chat box, and it is under testing, will be updated later!' }], updateAt: Date.now() }],
      activeSessionIndex: 0,

   }),
   mutations: {
      //push the message to the array 
      // single session used
      // ADD_MESSAGE(state, message) {
      //    state.messages.push(message);
      // },
      // update message as text chunk to realize stream 
      // single session used
      // UPDATE_MESSAGE(state, payload) {
      //    // console.log(payload);
      //    // console.log(state.messages[state.messageIndex].text);
      //    state.messages[state.messageIndex].text += payload;
      // },

      SET_MESSAGE_INDEX(state, payload) {
         state.messageIndex = payload;
      },

      UPDATE_SESSION_NAME(state, payload) {
         state.sessionName = payload;
      },
      ADD_SESSION(state, payload) {
         state.sessions.push(payload);
      },
      DELETE_SESSION(state, payload) {
         state.sessions.splice(payload, 1);
      },
      SET_ACTIVESESSION_INDEX(state, payload) {
         state.activeSessionIndex = payload;
      },
      //push the message to the array
      ADD_ACTIVESESSION_MESSAGE(state, message) {
         state.sessions[state.activeSessionIndex].messages.push(message);
      },
      UPDATE_ACTIVESESSION_MESSAGE(state, payload) {
         // console.log(payload);
         state.sessions[state.activeSessionIndex].messages[state.messageIndex].text += payload;
      },
      ADD_LOCAL_CHAT_DATA(state,payload){
         state.sessions = payload;
      },

      //set chat widget display
      SET_CHAT_WIDGET_DISPALY(state,payload){
         state.isChatOn =payload;
      }



   },
   actions: {
      // addMessage(context, message) {
      //    context.commit('ADD_MESSAGE', message);
      // },
      // updateMessage(context, payload) {
      //    context.commit('UPDATE_MESSAGE', payload);
      // },
      setMessageIndex(context, payload) {
         context.commit('SET_MESSAGE_INDEX', payload);
      },
      updateSessionName(context, payload) {
         context.commit('UPDATE_SESSION_NAME', payload);
      },
      addSession(context, payload) {
         context.commit("ADD_SESSION", payload);
      },
      deleteSession(context, payload) {
         context.commit("DELETE_SESSION", payload);
      },
      setActiveSessionIndex(context, payload) {
         context.commit("SET_ACTIVESESSION_INDEX", payload);
      },
      addActiveSessionMessage(context, message) {
         context.commit('ADD_ACTIVESESSION_MESSAGE', message);
      },
      updateActiveSessionMessage(context, payload) {
         context.commit("UPDATE_ACTIVESESSION_MESSAGE", payload);
      },
      addLocalChatData(context,payload){
         context.commit("ADD_LOCAL_CHAT_DATA",payload);
      },

      setChatDisplay(context,payload){
         context.commit('SET_CHAT_WIDGET_DISPALY',payload);
      }



   },
   getters: {
      getIsChatOn(state) {
         return state.isChatOn;
      },
      // getMessages(state) {
      //    return state.messages;
      // },
      // getNumMessages(state) {
      //    return state.messages.length;
      // },
      getMessageIndex(state) {
         return state.messageIndex;
      },
      getSessions(state) {
         return state.sessions;
      },
      getActiveSessionIndex(state) {
         return state.activeSessionIndex;
      },
      getActiveSession(state) {
         return state.sessions[state.activeSessionIndex];
      },
      getActiveSessionID(state) {
         return state.sessions[state.activeSessionIndex].id;
      },
      getActiveSessionTopic(state) {
         return state.sessions[state.activeSessionIndex].topic;
      },
      getActiveSessionMessages(state) {
         return state.sessions[state.activeSessionIndex].messages;
      },
      getNumActiveSessionMessages(state) {
         return state.sessions[state.activeSessionIndex].messages.length;
      },




   },

}

export default chatStore;
