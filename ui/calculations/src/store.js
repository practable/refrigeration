import { createStore } from 'vuex';
// import uiStore from './modules/uiStore.js'
// import logging from './modules/logging.js'
import dataStore from './modules/dataStore';
import loggingStore from './modules/logging';
import uiStore from './modules/uiStore';


const store = createStore({
    modules:{
        data: dataStore,
        logging: loggingStore,
        ui:uiStore,
    }
})

export default store;