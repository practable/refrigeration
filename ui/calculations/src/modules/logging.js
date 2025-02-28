// 17/09/24 Updated for use with new analytics server

const loggingStore = {
    state: () => ({
        uuid: '',                           //will be set from App.vue from localStorage
        isLoggingOn: true,                  //hard coded here
        logging_consent_given: true,       //User set in Consent.vue component
        hardware: '',           //will be set from the Logging.vue component - the general experiment name e.g. spinner or pendulum
        experiment: '',         //will be set from the Logging.vue component - the specific code for a single kit e.g. spin30
        course: '',      //will be set from the Logging.vue component - a course code, e.g. ed1 or cie3
       }),
       mutations:{
            SET_LOGGING_CONSENT(state, consent){
                state.logging_consent_given = consent;
            },
            SET_UUID(state, uuid){
                state.uuid = uuid;
            },
            SET_EXPERIMENT(state, experiment){
                state.experiment = experiment;
            },
            SET_HARDWARE(state, hardware){
                state.hardware = hardware;
            },
            SET_COURSE(state, course){
                state.course = course;
            }
       },
       actions:{
            setLoggingConsent(context, consent){
                context.commit('SET_LOGGING_CONSENT', consent);
            },
            setUUID(context, uuid){
                context.commit('SET_UUID', uuid);
            },
            setExperiment(context, experiment){
                context.commit('SET_EXPERIMENT', experiment)
            },
            setHardware(context, hardware){
                context.commit('SET_HARDWARE', hardware)
            },
            setCourse(context, course){
                context.commit('SET_COURSE', course)
            },
       },
       getters:{
           getLogConsent(state){
            return state.logging_consent_given;
            },
            getLogUUID(state){
                return state.uuid;
            },
            getExperiment(state){
                return state.experiment;
            },
            getHardware(state){
                return state.hardware;
            },
            getCourse(state){
                return state.course;
            },
            getIsLoggingOn(state){
                return state.isLoggingOn;
            }
       },  
  
  }

  export default loggingStore;
