<template>
    <div id='chat-widget' :style="[{ top: position.top + 'px', left: position.left + 'px' }, dialogueStyle]" @mousedown="startDrag"
        @mousemove="drag" @mouseup="endDrag" @mouseleave="endDrag">
        <!--  at the right lower corner position of the page: class="toast-container position-fixed bottom-0 end-0 p-3"  -->
        <div class="toast show" role="alert" ref="toastLive" aria-live="assertive" aria-atomic="true"
            data-bs-autohide='false'>
            <div class='toast-header'>
                <strong class="me-auto">Chat</strong>
                <!-- button to show the full window of the chatbox  -->
                <button @click="openModal" type="button" class="btn btn-outline-primary" data-bs-toggle="modal"
                    data-bs-target="#fullWindow">
                    <svg width="15px" height="20px" viewBox="0 0 512 512" version="1.1" xml:space="preserve"
                        xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                        <g id="_x37_14-_zoom_out__x2C__user_interface__x2C__ui__x2C_">
                            <g>
                                <polyline points="    26.7,330.048 26.7,486.139 182.924,486.139   "
                                    style="fill:none;stroke:#000000;stroke-width:25;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:2.6131;" />
                                <line
                                    style="fill:none;stroke:#000000;stroke-width:25;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:2.6131;"
                                    x1="26.7" x2="222.143" y1="486.139" y2="290.792" />
                                <polyline points="    486.25,182.962 486.25,26.814 330.025,26.814   "
                                    style="fill:none;stroke:#000000;stroke-width:25;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:2.6131;" />
                                <line
                                    style="fill:none;stroke:#000000;stroke-width:25;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:2.6131;"
                                    x1="486.25" x2="290.807" y1="26.814" y2="222.162" />
                            </g>
                        </g>
                        <g id="Layer_1" />
                    </svg>
                </button>
                <button type="button" class="btn-close" aria-label="Close" @click="closeChatWidget"></button>
                <!-- fullchat box has been disable until prompt has been tested -->
                <!-- <FullChatbox ref="fullwindow" /> -->
            </div>
            <div class="toast-body">
                <div id="message-wrapper">
                    <div id='message-container'>
                        <dialogue :message_list="getActiveSessionMessages" :message_count="getNumActiveSessionMessages"
                            @onMessageSent="handleMessageSent"  />

                    </div>
                </div>

            </div>
        </div>


    </div>


</template>

<script>
import 'bootstrap';
import { mapGetters, mapActions } from 'vuex';
import dialogue from './dialogue.vue';
import FullChatbox from './FullChatbox.vue';


export default {
    name: 'ChatWidget',
    components: {

        dialogue,
        FullChatbox,

    },
    props: {
    },
    emits: ['onMessageSent'],
    data() {
        return {
            user_input: '',
            isDragging: false,
            position: { top: 50, left: 50 }, // Initial position
            offset: { x: 0, y: 0 },
            dialogueHeight: '300px', // Initial height
        }
    },
    computed: {
        ...mapGetters([
            'getActiveSessionMessages',
            'getNumActiveSessionMessages',
            'getSessions',
            'getIsChatOn',
        ]),
        dialogueStyle() {
            return {
                '--dialogue-height': this.dialogueHeight,
            };
        },

    },
    watch: {

    },
    methods: {
        ...mapActions([
            'addActiveSessionMessage',
            'setChatDisplay',
        ]),

        //handle messages sent
        handleMessageSent(message) {
            this.addActiveSessionMessage(message);
            console.log(message);
            console.log(this.getActiveSessionMessages);
        },

        //open the fullscreen chat modal
        openModal() {
            if (this.$refs.fullwindow) {
                this.$refs.fullwindow.showModal();
            }
        },

        //close the chat widget on and off by  'getIsChatOn',
        closeChatWidget() {
            this.$emit('closeChatWidget');
        },


        startDrag(event) {
            this.isDragging = true;
            this.offset.x = event.clientX - this.position.left;
            this.offset.y = event.clientY - this.position.top;
        },
        drag(event) {
            if (this.isDragging) {
                this.position.left = event.clientX - this.offset.x;
                this.position.top = event.clientY - this.offset.y;
            }
        },
        endDrag() {
            this.isDragging = false;
        }


    }
}
</script>

<style scoped>
#chat-widget {
    position: absolute;
}

#message-wrapper {
    max-height: 100%;
    overflow: auto;
    padding: 10px;
    box-sizing: border-box;

}

#message-container {
    /* overflow: scroll; */
    overflow-y: auto;
    max-height: 100%;
    /* max height to show the message, 500px is too much for laptop */
    background-color: var(--background-color);
    /* padding: 10px;  
    box-sizing: border-box;  */
}

#bottom-container {
    min-height: 100px;
}


.header-admin {
    background-color: var(--background-color-warning);
    color: var(--text-color-inverted);
}

.header-hardware {
    background-color: var(--background-color-danger);
    color: var(--text-color-inverted);
}

.header-standard {
    background-color: var(--button-color-secondary);
    color: var(--text-color-inverted);
}
</style>