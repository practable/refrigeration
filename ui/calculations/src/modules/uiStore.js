//Store for variables that are common amongst multiple UI components. 


const uiStore = {
    state: () => ({
        isDraggable: true,
        consent_given: false,
        input_disabled: false,
        usesLocalStorage: false,        //can only use localStorage if the browser allows it.
       }),
       mutations:{
         SET_DRAGGABLE(state, draggable){
            state.isDraggable = draggable;
         },
         SET_CONSENT(state, consent){
            state.consent_given = consent;
         },
         SET_USES_LOCAL_STORAGE(state, set){
            state.usesLocalStorage = set;
         },

       },
       actions:{
         setDraggable(context, draggable){
             context.commit('SET_DRAGGABLE', draggable);
         },
         setConsent(context, consent){
            context.commit('SET_CONSENT', consent);
         },
         setUsesLocalStorage(context, set){
            context.commit('SET_USES_LOCAL_STORAGE', set);
         },

       },
       getters:{
         getDraggable(state){
             return state.isDraggable;
         },
         getConsent(state){
            return state.consent_given;
         },
         getUsesLocalStorage(state){
            return state.usesLocalStorage;
         },
          
         
       },  
  
  }

  export default uiStore;
