
////Store for sending commands through the dataSocket

const commandStore = {
    state: () => ({
        
        dataSocket: null,
        // 0 is closed, 1 is opened
        V1: 0,
        V2: 0,
        V3: 0,
        V4: 0,
        V5: 0,
        V6: 0,
        V7: 0,
        W1: 0,
        W2: 0,
        Comp: 0,
        light: 0,

       }),

       mutations:{
        SET_DATA_SOCKET(state, socket){
            state.dataSocket = socket;
        },
        SETV1(state,value) {
            state.V1 = value;
        },

        SETV2(state,value) {
            state.V2 = value;
        },

        SETV3(state,value) {
            state.V3 = value;
        },

        SETV4(state,value) {
            state.V4 = value;
        },

        SETV5(state,value) {
            state.V5 = value;
        },

        SETV6(state,value) {
            state.V6 = value;
        },

        SETV7(state,value) {
            state.V7 = value;
        },

        SETW1(state,value) {
            state.W1 = value;
        },

        SETW2(state,value) {
            state.W2 = value;
        },

        SETComp(state,value) {
            state.Comp = value;
        },

        SETlight(state,value) {
            state.light = value;
        },

 
       },
       actions:{
        setDataSocket(context, socket){
            context.commit("SET_DATA_SOCKET", socket);
        },

        //set the controllers value
        setV1({ commit }, value){
            commit('SETV1',value);
        },
        setV2({ commit }, value){
            commit('SETV2',value);
        },
        setV3({ commit }, value){
            commit('SETV3',value);
        },
        setV4({ commit }, value){
            commit('SETV4',value);
        },
        setV5({ commit }, value){
            commit('SETV5',value);
        },
        setV6({ commit }, value){
            commit('SETV6',value);
        },
        setV7({ commit }, value){
            commit('SETV7',value);
        },
        setV8({ commit }, value){
            commit('SETV8',value);
        },
        setW1({ commit }, value){
            commit('SETW1',value);
        },
        setW2({ commit }, value){
            commit('SETW2',value);
        },
        setComp({ commit }, value){
            commit('SETComp',value);
        },
        setlight({ commit }, value){
            commit('SETlight',value);
        },


        //send msg to server, in Vue file, use dispatch to use this function, in server side, check the JSON content and then change the parameter's value
        // 0- turn off, 1- turn on
        SENDV1CONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({ "valve":1, "state":0 })
                state.dataSocket.send(msg);
            
                //test on the  UI
                commit("SETV1",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({ "valve":1, "state":1 })
                state.dataSocket.send(msg);
            
                 //test on the  UI
                commit("SETV1",1);
            }
        },
        SENDV2CONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({ "valve":2, "state":0 })
                state.dataSocket.send(msg);
            
                //test on the  UI
                commit("SETV2",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({ "valve":2, "state":1 })
                state.dataSocket.send(msg);
                
                //test on the  UI
                commit("SETV2",1);
            }
        },

        SENDV3CONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({ "valve":3, "state":0 })
                state.dataSocket.send(msg);

                //test on the  UI
                commit("SETV3",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({ "valve":3, "state":1 })
                state.dataSocket.send(msg);

                 //test on the  UI
                 commit("SETV3",1);
            }
        },

        
        SENDV4CONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({ "valve":4, "state":0 })
                state.dataSocket.send(msg);

                //test on the  UI
                commit("SETV4",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({ "valve":4, "state":1 })
                state.dataSocket.send(msg);

                 //test on the  UI
                 commit("SETV4",1);
            }
        },

        
        SENDV5CONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({ "valve":5, "state":0 })
                state.dataSocket.send(msg);

                //test on the  UI
                commit("SETV5",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({ "valve":5, "state":1 })
                state.dataSocket.send(msg);

                 //test on the  UI
                 commit("SETV5",1);
            }
        },

        
        SENDV6CONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({ "valve":6, "state":0 })
                state.dataSocket.send(msg);

                //test on the  UI
                commit("SETV6", 0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({ "valve":6, "state":1 })
                state.dataSocket.send(msg);

                 //test on the  UI
                 commit("SETV6",1);
            }
        },

        
        SENDV7CONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({ "valve":7, "state":0 })
                state.dataSocket.send(msg);

                //test on the  UI
                commit("SETV7",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({ "valve":7, "state":1 })
                state.dataSocket.send(msg);

                 //test on the  UI
                 commit("SETV7",1);
            }
        },

        SENDW1CONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({"fans":0})
                state.dataSocket.send(msg);

                //test on the  UI
                commit("SETW1",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({"fans":1})
                state.dataSocket.send(msg);

                 //test on the  UI
                 commit("SETW1",1);
            }
        },

        // SENDW2CONTROL({ state, commit }, value) { 
        //     if (value == 0) {
        //         //connect to the server
        //         // let msg = JSON.stringify({ "valve":7, "state":0 })
        //         // state.dataSocket.send(msg);

        //         //test on the  UI
        //         commit("SETW2",0);
            
        //     } else if (value == 1) {
        //         // let msg = JSON.stringify({ "valve":7, "state":1 })
        //         // state.dataSocket.send(msg);

        //          //test on the  UI
        //          commit("SETW2",1);
        //     }
        // },

        SENDCOMPCONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({"comp":0})
                state.dataSocket.send(msg);

                //test on the  UI
                commit("SETComp",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({"comp":1})
                state.dataSocket.send(msg);

                 //test on the  UI
                 commit("SETComp",1);
            }
        },


        SENDLIGHTCONTROL({ state, commit }, value) { 
            if (value == 0) {
                //connect to the server
                let msg = JSON.stringify({"lights":0})
                state.dataSocket.send(msg);

                //test on the  UI
                commit("SETlight",0);
            
            } else if (value == 1) {
                let msg = JSON.stringify({"lights":1})
                state.dataSocket.send(msg);

                 //test on the  UI
                 commit("SETlight",1);
            }
        },

     

       },
       getters:{
        getDataSocket(state){
            return state.dataSocket;
        },

          
       },  
  
  }

  export default commandStore;