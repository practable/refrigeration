
const dataStore = {
    state: () => ({
        //measured data 
        measuredTime: 0,
        T1: 0,
        T2: 0,
        T3: 0,
        T4: 0,
        T5: 0,
        P1: 0,
        P2: 0,
        P3: 0,
        F: 0,
        E: 0,
        ASP: 0,

        // student calculation data
        H1: 0,
        H2: 0,
        H3: 0,
        H4: 0,
        H5: 0,
        m: 0,
        QL: 0,
        QH: 0,
        W: 0,
        COP: 0,
        n: 0,

        // Deviation data
        H1_Dev: "-",
        H2_Dev: "-",
        H3_Dev: "-",
        H4_Dev: "-",
        H5_Dev: "-",
        m_Dev: "-",
        QL_Dev: "-",
        QH_Dev: "-",
        W_Dev: "-",
        COP_Dev: "-",
        n_Dev: "-",

        // Saturated value 
        SaturT_P1: "-",
        SaturT_P2: "-",
        SaturP_T3: "-",
        SaturP_T5: "-",

        //img_data 
        img_data: null,

        //data confirmed
        MeasuerdDataConfirmed: 0,
        CalcuDataConfirmed: 0,

        //input expected error from server 
        measuredDataFeedback: null,

        //error message
        errormessage:"",
        feedbackMessageClass:'',

    }),
    mutations: {
        //set error messge in store
        SETErrorMessage(state, value){
            state.errormessage = value;
        },
        SETFeedbackMessageClass(state, value){
            state.feedbackMessageClass = value;
        },

        //set measured data feedback according to expected error from server response 
        SETMeasuerdDataFeedback(state, value) {
            state.measuredDataFeedback = value;
        },

        //set the data confirmed value according to the student input
        SETMeasuerdDataConfirmed(state, value) {
            state.MeasuerdDataConfirmed = value;
        },

        SETCalcuDataConfirmed(state, value) {
            state.CalcuDataConfirmed = value;
        },

        //set the measured parameters value according to the student input
        SETMeasuredTime(state, value) {
            state.measuredTime = value;
        },
        SETT1(state, value) {
            state.T1 = value;
        },
        SETT2(state, value) {
            state.T2 = value;
        },
        SETT3(state, value) {
            state.T3 = value;
        },
        SETT4(state, value) {
            state.T4 = value;
        },
        SETT5(state, value) {
            state.T5 = value;
        },
        SETP1(state, value) {
            state.P1 = value;
        },
        SETP2(state, value) {
            state.P2 = value;
        },
        SETP3(state, value) {
            state.P3 = value;
        },
        SETE(state, value) {
            state.E = value;
        },
        SETF(state, value) {
            state.F = value;
        },
        SETASP(state, value) {
            state.ASP = value;
        },

        //set the calculation data from students input
        SETH1(state, value) {
            state.H1 = value;
        },
        SETH2(state, value) {
            state.H2 = value;
        },
        SETH3(state, value) {
            state.H3 = value;
        },
        SETH4(state, value) {
            state.H4 = value;
        },
        SETH5(state, value) {
            state.H5 = value;
        },
        SETm(state, value) {
            state.m = value;
        },
        SETQL(state, value) {
            state.QL = value;
        },
        SETQH(state, value) {
            state.QH = value;
        },
        SETW(state, value) {
            state.W = value;
        },
        SETCOP(state, value) {
            state.COP = value;
        },
        SETn(state, value) {
            state.n = value;
        },

        // set deviation data from server
        SETH1_Dev(state, value) {
            state.H1_Dev = value;
        },
        SETH2_Dev(state, value) {
            state.H2_Dev = value;
        },
        SETH3_Dev(state, value) {
            state.H3_Dev = value;
        },
        SETH4_Dev(state, value) {
            state.H4_Dev = value;
        },
        SETH5_Dev(state, value) {
            state.H5_Dev = value;
        },
        SETm_Dev(state, value) {
            state.m_Dev = value;
        },
        SETQL_Dev(state, value) {
            state.QL_Dev = value;
        },
        SETQH_Dev(state, value) {
            state.QH_Dev = value;
        },
        SETW_Dev(state, value) {
            state.W_Dev = value;
        },
        SETCOP_Dev(state, value) {
            state.COP_Dev = value;
        },
        SETn_Dev(state, value) {
            state.n_Dev = value;
        },

        // set saturated data from server
        SETSaturT_P1(state, value) {
            state.SaturT_P1 = value;
        },
        SETSaturT_P2(state, value) {
            state.SaturT_P2 = value;
        },
        SETSaturP_T3(state, value) {
            state.SaturP_T3 = value;
        },
        SETSaturP_T5(state, value) {
            state.SaturP_T5 = value;
        },

        //set img data from server
        SETimg_data(state, value) {
            state.img_data = value;
        }

    },
    actions: {
        SetErrorMessage(context,value){
            context.commit('SETErrorMessage',value)
        },

        SetFeedbackMessageClass(context, value){
            context.commit('SETFeedbackMessageClass',value)
        },

        SetMeasuerdDataFeedback(context, value) {
            context.commit('SETMeasuerdDataFeedback', value)
        },

        //commit the data confirmed value according to the student input
        SetMeasuerdDataConfirmed(context, value) {
            context.commit('SETMeasuerdDataConfirmed', value)
        },

        SetCalcuDataConfirmed(context, value) {
            context.commit('SETCalcuDataConfirmed', value)
        },


        //commit the mutation of setting value of measured data 
        SetMeasuredTime(context, value) {
            context.commit('SETMeasuredTime', value);
        },
        SetT1(context, value) {
            context.commit('SETT1', value)
        },
        SetT2(context, value) {
            context.commit('SETT2', value)
        },
        SetT3(context, value) {
            context.commit('SETT3', value)
        },
        SetT4(context, value) {
            context.commit('SETT4', value)
        },
        SetT5(context, value) {
            context.commit('SETT5', value)
        },
        SetP1(context, value) {
            context.commit('SETP1', value)
        },
        SetP2(context, value) {
            context.commit('SETP2', value)
        },
        SetP3(context, value) {
            context.commit('SETP3', value)
        },
        SetE(context, value) {
            context.commit('SETE', value)
        },
        SetF(context, value) {
            context.commit('SETF', value)
        },
        SetASP(context, value) {
            context.commit('SETASP', value)
        },

        //commit the mutation of setting value of students calculation 
        SetH1(context, value) {
            context.commit('SETH1', value)
        },
        SetH2(context, value) {
            context.commit('SETH2', value)
        },
        SetH3(context, value) {
            context.commit('SETH3', value)
        },
        SetH4(context, value) {
            context.commit('SETH4', value)
        },
        SetH5(context, value) {
            context.commit('SETH5', value)
        },
        Setm(context, value) {
            context.commit('SETm', value)
        },
        SetQL(context, value) {
            context.commit('SETQL', value)
        },
        SetQH(context, value) {
            context.commit('SETQH', value)
        },
        SetW(context, value) {
            context.commit('SETW', value)
        },
        SetCOP(context, value) {
            context.commit('SETCOP', value)
        },
        Setn(context, value) {
            context.commit('SETn', value)
        },

        //commit the dev data from server
        SetH1_Dev(context, value) {
            context.commit('SETH1_Dev', value)
        },
        SetH2_Dev(context, value) {
            context.commit('SETH2_Dev', value)
        },
        SetH3_Dev(context, value) {
            context.commit('SETH3_Dev', value)
        },
        SetH4_Dev(context, value) {
            context.commit('SETH4_Dev', value)
        },
        SetH5_Dev(context, value) {
            context.commit('SETH5_Dev', value)
        },
        Setm_Dev(context, value) {
            context.commit('SETm_Dev', value)
        },
        SetQL_Dev(context, value) {
            context.commit('SETQL_Dev', value)
        },
        SetQH_Dev(context, value) {
            context.commit('SETQH_Dev', value)
        },
        SetW_Dev(context, value) {
            context.commit('SETW_Dev', value)
        },
        SetCOP_Dev(context, value) {
            context.commit('SETCOP_Dev', value)
        },
        Setn_Dev(context, value) {
            context.commit('SETn_Dev', value)
        },

        // commit saturated value from server
        SetSaturT_P1(context, value) {
            context.commit('SETSaturT_P1', value)
        },
        SetSaturT_P2(context, value) {
            context.commit('SETSaturT_P2', value)
        },
        SetSaturP_T3(context, value) {
            context.commit('SETSaturP_T3', value)
        },
        SetSaturP_T5(context, value) {
            context.commit('SETSaturP_T5', value)
        },

        //commit img_data value from server
        Setimg_data(context, value) {
            context.commit('SETimg_data', value)
        },

    },
    getters: {
        GetFeedbackMessageClass(state){
            return state.feedbackMessageClass
        },
        GetErrorMessage(state){
            return state.errormessage
        },

        GetMeasuerdDataFeedback(state) {
            return state.measuredDataFeedback
        },

        // get the confirmed state data
        GetMeasuerdDataConfirmed(state) {
            return state.MeasuerdDataConfirmed
        },

        GetCalcuDataConfirmed(state) {
            return state.CalcuDataConfirmed
        },


        // get the measured data
        GetMeasuredTime(state) {
            return state.measuredTime
        },
        GetT1(state) {
            return state.T1
        },
        GetT2(state) {
            return state.T2
        },
        GetT3(state) {
            return state.T3
        },
        GetT4(state) {
            return state.T4
        },
        GetT5(state) {
            return state.T5
        },
        GetP1(state) {
            return state.P1
        },
        GetP2(state) {
            return state.P2
        },
        GetP3(state) {
            return state.P3
        },
        GetE(state) {
            return state.E
        },
        GetF(state) {
            return state.F
        },
        GetASP(state) {
            return state.ASP
        },

        //get students calcuation data 
        GetH1(state) {
            return state.H1
        },
        GetH2(state) {
            return state.H2
        },
        GetH3(state) {
            return state.H3
        },
        GetH4(state) {
            return state.H4
        },
        GetH5(state) {
            return state.H5
        },
        Getm(state) {
            return state.m
        },
        GetQL(state) {
            return state.QL
        },
        GetQH(state) {
            return state.QH
        },
        GetW(state) {
            return state.W
        },
        GetCOP(state) {
            return state.COP
        },
        Getn(state) {
            return state.n
        },

        //get dev data
        GetH1_Dev(state) {
            return state.H1_Dev
        },
        GetH2_Dev(state) {
            return state.H2_Dev
        },
        GetH3_Dev(state) {
            return state.H3_Dev
        },
        GetH4_Dev(state) {
            return state.H4_Dev
        },
        GetH5_Dev(state) {
            return state.H5_Dev
        },
        Getm_Dev(state) {
            return state.m_Dev
        },
        GetQL_Dev(state) {
            return state.QL_Dev
        },
        GetQH_Dev(state) {
            return state.QH_Dev
        },
        GetW_Dev(state) {
            return state.W_Dev
        },
        GetCOP_Dev(state) {
            return state.COP_Dev
        },
        Getn_Dev(state) {
            return state.n_Dev
        },

        // get saturated value
        GetSaturT_P1(state) {
            return state.SaturT_P1
        },
        GetSaturT_P2(state) {
            return state.SaturT_P2
        },
        GetSaturP_T3(state) {
            return state.SaturP_T3
        },
        GetSaturP_T5(state) {
            return state.SaturP_T5
        },

        //get img_data
        Getimg_data(state) {
            return state.img_data
        },




    },
}

export default dataStore;
