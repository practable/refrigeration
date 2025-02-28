
const rawDataStore = {
    state: () => ({
        //define js variables  
        PS1_value: 0,
        PS2_value: 0,
        PS3_value: 0,
        TS1_value: 0,
        TS2_value: 0,
        TS3_value: 0,
        TS4_value: 0,
        TS5_value: 0,
        Flow_value: 0,
        Power_value: 0,
        TSA_value: 0,
        PSA_value: 0,
        HSA_value: 0,

        //time 
        Start_time: 0,
        Current_time: 0,//for chartjs and snapshot
        RecorderCurrentTime: 0, //for recorder
        RecorderStartTime: 0,
        Current_date: 0,
        data: [],
        snapdata: [],
        isRecording: false,
        // PS1_Array: [],
        // PS2_Array: [],
        // PS3_Array: [],
        // TS1_Array: [],
        // TS2_Array: [],
        // TS3_Array: [],
        // TS4_Array: [],
        // TS5_Array: [],
        // Flow_Array: [],
        // Power_Array: [],
        // TSA_Array: [],
        // PSA_Array: [],

        // url: '', //'ws://127.0.0.1:8181/test'
        // websocket: null,
        // receivedData: null,
        // jsonValue: null,


    }),
    getters: {
        // GETwebsocket(state) {
        //     return state.websocket
        // },
        // GETreceivedData(state) {
        //     return state.receivedData
        // },


        GetCurrentTS1(state) {
            return state.TS1_value
        },

        GetCurrentTS2(state) {
            return state.TS2_value
        },

        GetCurrentTS3(state) {
            return state.TS3_value
        },

        GetCurrentTS4(state) {
            return state.TS4_value
        },

        GetCurrentTS5(state) {
            return state.TS5_value
        },

        GetCurrentPS1(state) {
            return state.PS1_value
        },

        GetCurrentPS2(state) {
            return state.PS2_value
        },

        GetCurrentPS3(state) {
            return state.PS3_value
        },

        GetCurrentFlow(state) {
            return state.Flow_value
        },

        GetCurrentPower(state) {
            return state.Power_value
        },

        GetCurrentTSA(state) {
            return state.TSA_value
        },

        GetCurrentPSA(state) {
            return state.PSA_value
        },

        GetCurrentHSA(state) {
            return state.HSA_value
        },

        GETCurrentTime(state) {
            return state.Current_time
        },

        GETCurrentDate(state) {
            return state.Current_date
        },

        getData(state) {
            return state.data;
        },

        getMaxTime(state) {
            let time_max = -Infinity;
            state.data.forEach(d => {
                if (d.t > time_max) {
                    time_max = d.t;
                }
            });

            return time_max;
        },
        getMinTime(state) {
            let time_min = Infinity;
            state.data.forEach(d => {
                if (d.t < time_min) {
                    time_min = d.t;
                }
            });

            return time_min;
        },
        getIsRecording(state) {
            return state.isRecording;
        },
        getNumData(state) {
            return state.data.length;
        },

        getSnapData(state) {
            return state.snapdata;
        },
        getStartTime(state) {
            return state.Start_time;
        },
        //recoder
        getRecorderCurrentTime(state) {
            return state.RecorderCurrentTime;
        },
        getRecorderStartTime(state) {
            return state.RecorderStartTime;
        },




    },
    mutations: {

        // set js variables value according to the value from server, current values

        SETPS1_value(state, value) {
            state.PS1_value = value;
        },

        SETPS2_value(state, value) {
            state.PS2_value = value;
        },

        SETPS3_value(state, value) {
            state.PS3_value = value;
        },

        SETTS1_value(state, value) {
            state.TS1_value = value;
        },

        SETTS2_value(state, value) {
            state.TS2_value = value;
        },

        SETTS3_value(state, value) {
            state.TS3_value = value;
        },

        SETTS4_value(state, value) {
            state.TS4_value = value;
        },

        SETTS5_value(state, value) {
            state.TS5_value = value;
        },

        SETFlow_value(state, value) {
            state.Flow_value = value;
        },

        SETPower_value(state, value) {
            state.Power_value = value;
        },

        SETTSA_value(state, value) {
            state.TSA_value = value;
        },

        SETPSA_value(state, value) {
            state.PSA_value = value;
        },

        SETHSA_value(state, value) {
            state.HSA_value = value;
        },

        //record all value from server in a array, and this will use for the realtime chart display
        // SETPS1_Array(state) {
        //     state.PS1_Array.push(state.PS1_value);
        // },

        // SETPS2_Array(state) {
        //     state.PS2_Array.push(state.PS2_value);
        // },

        // SETPS3_Array(state) {
        //     state.PS3_Array.push(state.PS3_value);
        // },

        // SETTS1_Array(state) {
        //     state.TS1_Array.push(state.TS1_value);
        // },

        // SETTS2_Array(state) {
        //     state.TS2_Array.push(state.TS2_value);
        // },

        // SETTS3_Array(state) {
        //     state.TS3_Array.push(state.TS3_value);
        // },

        // SETTS4_Array(state) {
        //     state.TS4_Array.push(state.TS4_value);
        // },

        // SETTS5_Array(state) {
        //     state.TS5_Array.push(state.TS5_value);
        // },

        // SETFlow_Array(state) {
        //     state.Flow_Array.push(state.Flow_value);
        // },

        // SETPower_Array(state) {
        //     state.Power_Array.push(state.Power_value);
        // },

        // SETATS_Array(state) {
        //     state.ATS_Array.push(state.ATS_value);
        // },

        // SETAPS_Array(state) {
        //     state.APS_Array.push(state.APS_value);
        // },

        // functions of data recoder and snapshot, including the time and data add or delete 
        SET_CURRENT_TIME(state, value) {
            state.Current_time = value;
        },
        SET_CURRENT_DATE(state, value) {
            state.Current_date = value;
        },

        SET_START_TIME(state, value) {
            state.Start_time = value;
        },
        SET_IS_RECORDING(state, set) {
            state.isRecording = set;
        },
        CLEAR_ALL_DATA(state) {
            state.data = [];
        },
        ADD_DATA(state, object) {
            state.data.push(object);
        },
        ADD_SNAP_DATA(state, object) {
            state.snapdata.push(object);
        },
        DELETE_DATA(state, id) {
            state.data.splice(id, 1);
        },
        DELETE_SNAP_DATA(state) {
            state.snapdata = [];
        },
        ADD_SNAP_LOCAL_DATA(state, value) {
            state.snapdata = value;
        },
        SET_RECORDER_CURRENT_TIME(state, value) {
            state.RecorderCurrentTime = value;
        },
        SET_RECORDER_START_TIME(state, value) {
            state.RecorderStartTime = value;
        }

    },
    actions: {

        //set the sensors value
        setPS1_value({ commit }, value) {
            commit('SETPS1_value', value);
        },
        setPS2_value({ commit }, value) {
            commit('SETPS2_value', value);
        },
        setPS3_value({ commit }, value) {
            commit('SETPS3_value', value);
        },
        setTS1_value({ commit }, value) {
            commit('SETTS1_value', value);
        },
        setTS2_value({ commit }, value) {
            commit('SETTS2_value', value);
        },
        setTS3_value({ commit }, value) {
            commit('SETTS3_value', value);
        },
        setTS4_value({ commit }, value) {
            commit('SETTS4_value', value);
        },
        setTS5_value({ commit }, value) {
            commit('SETTS5_value', value);
        },
        setFlow_value({ commit }, value) {
            commit('SETFlow_value', value);
        },
        setPower_value({ commit }, value) {
            commit('SETPower_value', value);
        },
        setTSA_value({ commit }, value) {
            commit('SETTSA_value', value);
        },
        setPSA_value({ commit }, value) {
            commit('SETPSA_value', value);
        },
        setHSA_value({ commit }, value) {
            commit('SETHSA_value', value);
        },

        //set time
        setCurrentTime(context, value) {
            context.commit('SET_CURRENT_TIME', value);
        },
        setCurrentDate(context, value) {
            context.commit('SET_CURRENT_DATE', value);
        },
        setStartTime(context, value) {
            context.commit('SET_START_TIME', value);
        },
        setIsRecording(context, value) {
            context.commit('SET_IS_RECORDING', value);
        },
        clearAllData(context) {
            context.commit('CLEAR_ALL_DATA');
        },
        addData(context, object) {
            context.commit('ADD_DATA', object);
        },
        addSnapData(context, object) {
            context.commit('ADD_SNAP_DATA', object);
            // console.log(object);
        },
        deleteData(context, dataId) {
            context.commit('DELETE_DATA', dataId);
        },
        deleteSnapData(context) {
            context.commit('DELETE_SNAP_DATA');
        },
        addLocalSnapData(context, value) {
            context.commit('ADD_SNAP_LOCAL_DATA', value);
            // console.log(value);
        },
        setRecorderCurrentTime(context, value) {
            context.commit('SET_RECORDER_CURRENT_TIME', value);
        },
        setRecorderStartTime(context, value) {
            context.commit('SET_RECORDER_START_TIME', value);
        },

    }
}

export default rawDataStore