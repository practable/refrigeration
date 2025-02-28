<template>
    <div v-for="(session, index) in sessionList" :key="index" :id="index" class="session-item"
        :class="{ active: activeSessionIndex === index }" @click="toggleActive(index)">

        <div class="name"> {{ session.topic }}</div>

        <div class="count-time">
            <div class="count">
                {{ session.messages ? session.messages.length : 0 }} Dialogue

            </div>
            <div class="time">
                {{ getFormattedTime(session.updateAt) }}
            </div>
        </div>

        <div class="mask"></div>

        <div class="btn-wrapper">
            <button type="button" class="btn-close" aria-label="Close"
                @click.stop="showModalDelete = true, getDeleteSessionIndex(index)"></button>
        </div>


    </div>

    <div class="newsession">
        <button class="btn btn-light newsessionbutton" @click="handleCreateSession">new
            chat</button>
    </div>

    <!-- <button @click="showModalDelete = true">test modal</button> -->

    <popConfirm :isVisible="showModalDelete" @close="showModalDelete = false">
        <h2>Confirm</h2>
        <p>Are you sure you want to delete this session?</p>
        <button @click="handleDeleteSession(deleteSessionIndex), showModalDelete = false">Yes</button>
        <button @click="showModalDelete = false"> No</button>
    </popConfirm>

</template>


<script>
import popConfirm from './elements/popconfirm.vue'
import { mapActions, mapGetters } from 'vuex';

export default {
    name: 'SessionItem',
    props: {
        sessionList: Array,

    },
    // emits: ['delete'], //emit delete function to another vue to control delete function
    components: {
        popConfirm,

    },
    // created(){
    //     this.handleCreateSession();
    // },
    data() {
        return {
            // isActive: false,
            activeSessionIndex: null,
            showModalDelete: false,
            idNewSession: null,
            deleteSessionIndex: null,

        }
    },
    computed: {
        ...mapGetters([
            'getMessages',
            'getNumMessages',
            'getActiveSessionIndex',
            'getActiveSessionMessages',
            'getLogUUID',
            'getSessions',
        ]),
    },
    watch: {

    },
    methods: {
        ...mapActions([
            'addMessage',
            'addSession',
            'deleteSession',
            'setActiveSessionIndex',

        ]),

        // toggleActive() {
        //     this.isActive = !this.isActive;
        // },
        toggleActive(index) {
            // if the active get the index, if already have index then null :this.activeSessionIndex = this.activeSessionIndex === index ? null : index;
            // this.activeSessionIndex = this.activeSessionIndex === index ? null : index;
            this.activeSessionIndex = index;
            this.setActiveSessionIndex(this.activeSessionIndex);
            // console.log(this.activeSessionIndex);
            // console.log(this.getActiveSessionIndex);
            // console.log(this.getActiveSessionMessages);
        },
        handleCreateSession() {
            this.idNewSession = Date.now();
            let newSession = { id: this.idNewSession, username: this.getLogUUID, topic: "New session", messages: [{ sender: "Welcome", time: new Date().getTime(), text: 'This is chat box, and my name is atomic hydrogen.I can help you understand and navigate the Single Tube Condenser experiment. If you need assistance with any specific features of the user interface (UI), how to operate the experiment, or have questions about the theory behind the experiment, feel free to ask!' }, { sender: "Reminder", time: new Date().getTime(), text: 'You are not talking to a human - Please be aware that due to the nature of this technology, responses may include inaccurate, fictitious or completely wrong information. Please refer to our AI Guidance (https://information-services.ed.ac.uk/computing/comms-and-collab/elm/guidance-for-working-with-generative-ai)' }], updateAt: Date.now() };
            this.addSession(newSession);
        },

        getDeleteSessionIndex(index) {
            this.deleteSessionIndex = index;
            console.log(this.deleteSessionIndex);
            console.log(this.getSessions.length);
        },

        handleDeleteSession(index) {
            console.log("delete session" + index);

            if (this.getSessions.length >= 2) {
                // Emit the delete event with the session details :this.sessionList[index]
                // this.$emit("delete", index );
                this.deleteSession(index); //deleteSession in the chatstore
                this.activeSessionIndex = 0;
                this.setActiveSessionIndex(this.activeSessionIndex);
            } else {
                console.log("can't delete the last one" + this.getSessions.length)
            }

        },

        getFormattedTime(time_ms) {
            let date = new Date(time_ms);
            let yyyy = date.getFullYear();
            let mm = date.getMonth() + 1; // Months are zero-based
            let dd = date.getDate();
            let hh = date.getHours();
            let min = date.getMinutes();
            let ss = date.getSeconds();

            // Pad single-digit day, month, hour, minute, and second with leading zeros
            if (mm < 10) mm = '0' + mm;
            if (dd < 10) dd = '0' + dd;
            if (hh < 10) hh = '0' + hh;
            if (min < 10) min = '0' + min;
            if (ss < 10) ss = '0' + ss;

            // Format for date and time
            let formattedDate = `${yyyy}-${mm}-${dd}`;
            let formattedTime = `${hh}:${min}:${ss}`;

            if (Date.now() - date.getTime() > 24 * 60 * 60 * 1000) {
                // Return date and time if older than 24 hours
                return `${formattedDate} ${formattedTime}`;
            } else {
                // Return only the time if within the last 24 hours
                // return formattedTime;
                // still return format with the date
                return `${formattedDate} ${formattedTime}`
            }
        },

    }

}

</script>

<style>
.newsession {
    position: absolute;
    bottom: 20px;
    /* right: 0;  */
    display: flex;
    justify-content: flex-end;
    width: 100%;


    .newsessionbutton {
        margin-right: 20px;
    }

}

.session-item {
    margin-left: 15px;
    margin-top: 20px;
    padding: 20px;
    background-color: var(--background-color);
    color: var(--text-color);
    border-radius: 5px;
    width: 200px;
    position: relative;
    cursor: grab;
    overflow: hidden;

    .name {

        font-size: 14px;
        font-weight: 700;
        width: 50px;

        /* color: rgba(rgb(0, 0, 0), 0.8); */
    }

    .count-time {

        margin-top: 10px;
        font-size: 10px;
        /* color: rgba(black, 0.5);
                 */
        display: flex;
        justify-content: space-between;
    }

    &.active {

        transition: all 0.12s linear;
        border: 2px solid #1d93ab;
    }


    &:hover {

        .mask {
            opacity: 1;
            left: 0;
        }
    }

    .mask {

        transition: all 0.2s ease-out;
        position: absolute;
        background-color: rgba(0, 0, 0, 0.05);
        width: 100%;
        height: 100%;
        top: 0;
        left: -100%;
        opacity: 0;
    }

    .btn-wrapper {
        color: rgba(black, 0.5);
        transition: all 0.2s ease-out;
        position: absolute;
        top: 20px;
        right: 20px;
        /* z-index: 10; */
        /* opacity: 0; */

    }

}
</style>