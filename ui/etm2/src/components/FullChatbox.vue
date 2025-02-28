<template>
    <!-- Modal -->
    <div class="modal fade" ref="modal" id="fullWindow" tabindex="-1" aria-labelledby="exampleModalLabel"
        aria-hidden="true" :style="dialogueStyle">
        <div class="modal-dialog modal-fullscreen" >
            <div class="modal-content" >
                <div class="modal-header">
                    <h1 class="modal-title fs-5 " id="exampleModalLabel">Chat_STC Experiment (atomic hydrogen) </h1>
                    <!-- <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button> -->
                    <div class="button-container">
                        <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                    </div>

                </div>
                <div class="modal-body">
                    <div class="home-view">
                        <div class="chat-panel" >
                            <!-- sessions list for different dialogues -->
                            <div class="session-panel">

                                <SessionItem :sessionList="getSessions" />
                                <!-- @delete="deleteSession" -->

                            </div>
                            <!-- details in one session -->
                            <div class="message-panel" >
                                <div class="header">
                                    <div class="front">
                                        <div class="title">Session</div>
                                        <!-- <div v-if="isEdit" class="title">

                                        </div> -->
                                        <!-- <div v-else class="title">Session 1</div> -->
                                        <div class="description">
                                            {{ this.getNumActiveSessionMessages }} dialogues
                                        </div>
                                    </div>
                                    <div class="rear">

                                    </div>
                                </div>
                                <dialogue :message_list="getActiveSessionMessages"
                                    :message_count="getNumActiveSessionMessages" @onMessageSent="handleMessageSent" />
                            </div>
                            <!-- <el-divider :border-style="'solid'" /> -->
                        </div>
                    </div>
                </div>
                <div class="modal-footer">
                    <!-- <button type="button" class="btn btn-secondary" data-bs-dismiss="modal"  >Close</button> -->
                    <!-- 
                    <div class="input-group mt-3">
                        <input type="text" class="form-control" v-model='user_input' @keydown.enter="sendMessage"
                            placeholder="Enter message..." aria-label="message input" aria-describedby="user-input">
                        <button class="button-toolbar button-primary" type="button" id="user-input-submit"
                            @click="sendMessage">
                            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor"
                                class="bi bi-send" viewBox="0 0 16 16">
                                <path
                                    d="M15.854.146a.5.5 0 0 1 .11.54l-5.819 14.547a.75.75 0 0 1-1.329.124l-3.178-4.995L.643 7.184a.75.75 0 0 1 .124-1.33L15.314.037a.5.5 0 0 1 .54.11ZM6.636 10.07l2.761 4.338L14.13 2.576 6.636 10.07Zm6.787-8.201L1.591 6.602l4.339 2.76 7.494-7.493Z" />
                            </svg>
                        </button>
                    </div> -->

                    <!-- <button type="button" class="btn btn-primary">Save changes</button> -->
                </div>
            </div>
        </div>
    </div>

</template>


<script>
import { mapActions, mapGetters } from 'vuex';
import SessionItem from "./SessionItem.vue";
import dialogue from "./dialogue.vue";

export default {
    name: 'FullChatbox',
    props: {

    },
    components: {
        SessionItem,
        dialogue,
    },
    data() {
        return {
            isActive: false,
            dialogueHeight: '70vh',
        }
    },
    computed: {
        ...mapGetters([
            'getSessions',
            'getActiveSessionIndex',
            'getActiveSessionMessages',
            'getNumActiveSessionMessages',
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
            'addSession',
            'addActiveSessionMessage',
            'setSessionTopic',
        ]),

        handleMessageSent(message) {
            this.addActiveSessionMessage(message);

            if (this.getNumActiveSessionMessages ==3 ){
                var topic = this.getActiveSessionMessages[2].text.substring(0,10);
                this.setSessionTopic(topic);
            };
            console.log(topic);
            console.log(message);
            console.log(this.getActiveSessionMessages);
        },


        showModal() {
            const modalElement = this.$refs.modal;
            console.log(modalElement);
            if (modalElement) {
                const modal = new bootstrap.Modal(modalElement, {
                    backdrop: false,
                });
                modal.show();
            }

            // // Remove the backdrop dynamically
            // setTimeout(() => {
            //     const backdrop = document.querySelector('.modal-backdrop');
            //     console.log(backdrop);
            //     if (backdrop) {
            //         backdrop.parentNode.removeChild(backdrop); // Remove backdrop

            //     }
            // }, 300); // Delay to ensure modal is shown


        },

    }

}



</script>

<style scoped>
.button-container {
    margin-left: auto;
    display: flex;
    align-items: center;
}

.modal {
    /* delete the padding between the header/footer and body */
    --bs-modal-padding: 0rem;
    height: 100vh;
}


.home-view {
    /* display: flex; */
    /* width: 100%;
    justify-content: center; */
    /* height: 100%; */


    .chat-panel {
        display: flex;
        /* border-radius: 20px; */
        background-color: white;
        /* overflow: hidden;   */

        /* box-shadow: 0 0 20px 20px rgba(black, 0.05);
        margin-top: 0px; */

        .session-panel {
            overflow: scroll;
            background-color: var(--background-color-inverted);
            color: var(--text-color-inverted);
            width: 290px;
            /* border-top-left-radius: 20px;
            border-bottom-left-radius: 20px; */
            /* padding: 20px; */
            position: relative;
            /* border-right: 1px solid rgba(black, 0.07); */

            .title {
                margin-top: 20px;
                font-size: 20px;
            }

            .description {
                /* color: var(--text-color-inverted); */
                font-size: 10px;
                margin-top: 10px;
                margin-bottom: 10px;
            }
        }


    }

    .message-panel {
        /* display: flex; */

        width: 90%;
        /* height: 100%; */
        max-height: 100%;

        /* background-color: aqua; */
        .header {
            padding: 20px 20px 0 20px;
            display: flex;
            justify-content: space-between;
            border-bottom: 0.1ch solid;
            /* border-top-left-radius: 20px; */
            /* border-bottom-left-radius: 5px; */
            /* background-color: var(--background-color);
                color: var(--text-color); */

            .front {
                .title {
                    color: rgba(black, 0.7);
                    font-size: 20px;
                }

                .description {
                    margin-top: 10px;
                    color: rgba(black, 0.5);
                }
            }


            .rear {
                display: flex;
                align-items: center;
            }
        }

    }




}
</style>