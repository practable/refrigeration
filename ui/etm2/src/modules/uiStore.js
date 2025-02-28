//Store for variables that are common amongst multiple UI components. 


const uiStore = {
   state: () => ({
      isDataRecorderOn: false,    //is the Data Recorder element active
      isDraggable: true,
      usesLocalStorage: false,        //can only use localStorage if the browser allows it.
      colour_index: 0,
      v1color: '#808080',  //valves color change
      v2color: '#808080',
      v3color: '#808080',
      v4color: '#808080',  
      v5color: '#808080',
      v6color: '#808080',
      v7color: '#808080',

      w1color: '#808080',
      // w2color: '#ffffff',
      compcolor: '#808080',

      lightcolor: '#808080',


      //chart.js
      realTimeChart: null,

      //snapshot 
      valuePost: 0,     
      
      //snapsLocalStorage
      snapsLocalStorage:[],



   }),
   mutations: {
      SET_DATA_RECORDER(state, set) {
         state.isDataRecorderOn = set;
      },
      SET_DRAGGABLE(state, draggable) {
         state.isDraggable = draggable;
      },
      SET_COLOUR_INDEX(state, index) {
         state.colour_index = index
      },
      SET_USES_LOCAL_STORAGE(state, set) {
         state.usesLocalStorage = set;
      },

      // ADD_HIGHLIGHT_POSITION(state, position) {
      //    state.highlightedPositions = position;
      // },
      // CLEAR_HIGHLIGHT_POSITION(state) {
      //    state.highlightedPositions = {};
      // },

      // SHOW_HIGHLIGHT(state) {
      //    state.isHighlightVisiable = true;
      // },

      // HIDE_HIGHLIGHT(state) {
      //    state.isHighlightVisiable = false;
      // },

      SETV1openedcolor(state) {
         state.v1color = "#008000";
      },
      SETV1closecolor(state) {
         state.v1color = "#808080";
      },
      SETV1waitcolor(state) {
         state.v1color = "#ff0000";
      },

      SETV2openedcolor(state) {
         state.v2color = "#008000";
      },
      SETV2closecolor(state) {
         state.v2color = "#808080";
      },
      SETV2waitcolor(state) {
         state.v2color = "#ff0000";
      },

      SETV3openedcolor(state) {
         state.v3color = "#008000";
      },
      SETV3closecolor(state) {
         state.v3color = "#808080";
      },
      SETV3waitcolor(state) {
         state.v3color = "#ff0000";
      },

      SETV4openedcolor(state) {
         state.v4color = "#008000";
      },
      SETV4closecolor(state) {
         state.v4color = "#808080";
      },
      SETV4waitcolor(state) {
         state.v4color = "#ff0000";
      },


      SETV5openedcolor(state) {
         state.v5color = "#008000";
      },
      SETV5closecolor(state) {
         state.v5color = "#808080";
      },
      SETV5waitcolor(state) {
         state.v5color = "#ff0000";
      },


      SETV6openedcolor(state) {
         state.v6color = "#008000";
      },
      SETV6closecolor(state) {
         state.v6color = "#808080";
      },
      SETV6waitcolor(state) {
         state.v6color = "#ff0000";
      },


      SETV7openedcolor(state) {
         state.v7color = "#008000";
      },
      SETV7closecolor(state) {
         state.v7color = "#808080";
      },
      SETV7waitcolor(state) {
         state.v7color = "#ff0000";
      },


      SETw1ONcolor(state) {
         state.w1color = "#008000";
      },
      SETw1OFFcolor(state) {
         state.w1color = '#808080';
      },
      SETw1waitcolor(state) {
         state.w1color = "#ff0000";
      },

      
      SETw2ONcolor(state) {
         state.w2color = "#008000";
      },
      SETw2OFFcolor(state) {
         state.w2color = '#808080';
      },
      SETw2waitcolor(state) {
         state.w2color = "#ff0000";
      },

      SETcompONcolor(state) {
         state.compcolor = "#008000";
      },
      SETcompOFFcolor(state) {
         state.compcolor = '#808080';
      },
      SETcompwaitcolor(state) {
         state.compcolor = "#ff0000";
      },

      SETlightONcolor(state) {
         state.lightcolor = "#bbc34a";
      },
      SETlightOFFcolor(state) {
         state.lightcolor = '#808080';
      },
      SETlightwaitcolor(state) {
         state.lightcolor = "#ff0000";
      },
      //chart
      SETChart(state,value){
         state.realTimeChart = value;
      },
      // snapshot value post
      SETValuePost(state,value){
         state.valuePost = value;
      }


   },
   actions: {

      // updateHighlight({ state,commit },  { xPercentage, yPercentage }) {
      //    commit("ADD_HIGHLIGHT_POSITION",{xPercentage, yPercentage})
      //    commit("SHOW_HIGHLIGHT");
      //    console.log(state.highlightedPositions);
      // },

      // removeHighlight({ commit }) {
      //    commit("CLEAR_HIGHLIGHT_POSITION")
      //    commit("HIDE_HIGHLIGHT");
      //    console.log("bbbb");
      // },

      //chart
      setChart(context,value){
         context.commit("SETChart",value)
      },
      //snapshot 
      setValuePost(context,value){
         context.commit("SETValuePost",value)
      },

      setV1color(context, value) {
         if (value == 1) {
            context.commit("SETV1openedcolor");
         } else if (value == 0) {
            context.commit("SETV1closecolor");
         } else if (value == 2) {
            context.commit("SETV1waitcolor");
         } else {
            console.log("V1 controller error");
         }
      },
      setV2color(context, value) {
         if (value == 1) {
            context.commit("SETV2openedcolor");
         } else if (value == 0) {
            context.commit("SETV2closecolor");
         } else if (value == 2) {
            context.commit("SETV2waitcolor");
         } else {
            console.log("V2 controller error");
         }
      },
      setV3color(context, value) {
         if (value == 1) {
            context.commit("SETV3openedcolor");
         } else if (value == 0) {
            context.commit("SETV3closecolor");
         } else if (value == 2) {
            context.commit("SETV3waitcolor");
         } else {
            console.log("V3 controller error");
         }
      },

      setV4color(context, value) {
         if (value == 1) {
            context.commit("SETV4openedcolor");
         } else if (value == 0) {
            context.commit("SETV4closecolor");
         } else if (value == 2) {
            context.commit("SETV4waitcolor");
         } else {
            console.log("V4 controller error");
         }
      },
      setV5color(context, value) {
         if (value == 1) {
            context.commit("SETV5openedcolor");
         } else if (value == 0) {
            context.commit("SETV5closecolor");
         } else if (value == 2) {
            context.commit("SETV5waitcolor");
         } else {
            console.log("V5 controller error");
         }
      },
      setV6color(context, value) {
         if (value == 1) {
            context.commit("SETV6openedcolor");
         } else if (value == 0) {
            context.commit("SETV6closecolor");
         } else if (value == 2) {
            context.commit("SETV6waitcolor");
         } else {
            console.log("V6 controller error");
         }
      },
      setV7color(context, value) {
         if (value == 1) {
            context.commit("SETV7openedcolor");
         } else if (value == 0) {
            context.commit("SETV7closecolor");
         } else if (value == 2) {
            context.commit("SETV7waitcolor");
         } else {
            console.log("V7 controller error");
         }
      },

      setW1color(context, value) {
         if (value == 1) {
            context.commit("SETw1ONcolor");
         } else if (value == 0) {
            context.commit("SETw1OFFcolor");
         } else if (value == 2) {
            context.commit("SETw1waitcolor");
         } else {
            console.log("W1 controller error");
         }
      },

      // setW2color(context, value) {
      //    if (value == 1) {
      //       context.commit("SETw2ONcolor");
      //    } else if (value == 0) {
      //       context.commit("SETw2OFFcolor");
      //    } else if (value == 2) {
      //       context.commit("SETw2waitcolor");
      //    } else {
      //       console.log("W2 controller error");
      //    }
      // },

      setCOMPcolor(context, value) {
         if (value == 1) {
            context.commit("SETcompONcolor");
         } else if (value == 0) {
            context.commit("SETcompOFFcolor");
         } else if (value == 2) {
            context.commit("SETcompwaitcolor");
         } else {
            console.log("Compressor controller error");
         }
      },

      setlightcolor(context, value) {
         if (value == 1) {
            context.commit("SETlightONcolor");
         } else if (value == 0) {
            context.commit("SETlightOFFcolor");
         } else if (value == 2) {
            context.commit("SETlightwaitcolor");
         } else {
            console.log("lights controller error");
         }
      },

      setDataRecorder(context, set) {
         context.commit("SET_DATA_RECORDER", set);
      },
      setDraggable(context, draggable) {
         context.commit('SET_DRAGGABLE', draggable);
      },
      updateColourIndex(context) {
         let index = (context.state.colour_index + 1) % 6
         context.commit('SET_COLOUR_INDEX', index);
      },
      setUsesLocalStorage(context, set) {
         context.commit('SET_USES_LOCAL_STORAGE', set);
      },


   },
   getters: {
      getIsDataRecorderOn(state) {
         return state.isDataRecorderOn;
      },
      getDraggable(state) {
         return state.isDraggable;
      },
      getColourIndex(state) {
         return state.colour_index;
      },

      //chart function
      getChart(state){
         return state.realTimeChart;
      },
      //snapshot to chart value post
      getValuePost(state){
         return state.valuePost;
      },
      //snaps local storage
      getSnapsLocalStorage(state){
         return state.snapsLocalStorage;
      },
      getUsesLocalStorage(state) {
         return state.usesLocalStorage;
      },


   },

}

export default uiStore;
