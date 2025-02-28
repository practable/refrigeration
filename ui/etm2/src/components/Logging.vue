// To add: scrolling event log?
// To add: open and close workspace - should work with practable-component mutation
// To add: downloaded data - get from click download button?

<template>
  <div></div>
</template>

<script>
import { mapGetters } from 'vuex'
import axios from 'axios';
import config from '../config/logging-config'

export default {

  name: 'Logging',
  data () {
    return {
      instance_path: '',        //required for logging to instance - get from URL params
      la_auth: '',              //required for logging to instance - get from URL params
      input_listener_ids: [],   //for storing the elements that already have listeners attached
      
    }
  },
  computed:{
    ...mapGetters([
      'getLogUUID',
      'getSessionExpired',
      //'getIsChatOn',    //add back in with chat component
      //'getMessages',
      //'getNumMessages',
      'getDataURL',
      'getLogConsent',
      'getCourse',
      'getHardware',
      'getExperiment'
    ]),
    
  },
  watch:{
      //likely to have to watch here for logging URL to be obtained and then can enable logging?
      //Update the base logging URL
      getSessionExpired(expired){
          if(expired){
            let log = this.createSessionExpiredLog();
            this.sendLog(log);
          }
      },
      getDataURL(url){
          this.setExperiment(url);
      }
      //INCLUDE THIS ONCE THE CHAT COMPONENT IS BACK IN
      // getNumMessages(){
      //   let messages = this.getMessages;
      //   let latest_message_level = messages[messages.length - 1].level;
      //     if(latest_message_level == 'WARN' || latest_message_level == 'ERROR' || latest_message_level == 'FATAL'){
      //       let log = this.createExperimentLog(messages[messages.length - 1]);
      //       this.sendLog(log);
      //     }
      // },

  },
  created(){
      
  },
  mounted(){
    window.addEventListener("DOMContentLoaded", (event) => {

      try {
        
        let query = new URLSearchParams(window.location.search);
        this.la_auth = query.get('la');
        let la_host = query.get('lh');
        this.instance_path = decodeURIComponent(la_host);

        //get course query parameter
        let course = query.get('course');
        if(course != null){
          this.$store.dispatch('setCourse', course);
        } else{
          this.$store.dispatch('setCourse', 'none');
        }

        //get hardware query parameter
        let hardware = query.get('hardware');
        if(hardware != null){
          this.$store.dispatch('setHardware', hardware);
        } else{
          this.$store.dispatch('setHardware', 'none');
        }

      } catch (e) {
          console.log("error accessing query params");
      }

      this.createAndSendSessionStartLog();   //will run everytime the component mounts

      //all click events are logged
      if(config.click_logs_on){
        window.addEventListener("click", (event) => {
              let log = this.createClickLog(event);
              this.sendLog(log);
          });
      }

      if(config.mouse_enter_logs_on){
        this.AddMouseEnterListeners();
      }
        
      
      this.AddNewInputListeners();
      this.AddHotkeyListener();
      this.AddDragDropListeners();

      config.interval_logs.forEach(log => {
            this.AddIntervalLog(log);
      });

      //needs to listen for DOM mutations when a new component is added and refresh to listen for any added inputs
      // Select the node that will be observed for mutations
      const targetNode = document.getElementById("component-grid");

      // Options for the observer (which mutations to observe)
      const config_mutations = { attributes: false, childList: true, subtree: true };

      // Callback function to execute when mutations are observed
      const callback = (mutationList, observer) => {
        for (const mutation of mutationList) {
          mutation.addedNodes.forEach(node => {
            if (node instanceof HTMLElement) {
              if(node.querySelectorAll('input').length > 0) {
                  this.AddNewInputListeners();
              }

              if(node.classList.contains('practable-component')){
                this.createAndSendComponentOpenedLog(node);
              }
            }
          });

          mutation.removedNodes.forEach(node => {
            if (node instanceof HTMLElement) {
              if(node.querySelectorAll('input').length > 0) {
                  this.removeAllInputListeners();
                  this.AddNewInputListeners();
              }

              if(node.classList.contains('practable-component')){
                this.createAndSendComponentClosedLog(node);
              }
            }
          });
        }
      };
      // Create an observer instance linked to the callback function
      const observer = new MutationObserver(callback);
      // Start observing the target node for configured mutations
      observer.observe(targetNode, config_mutations);
      })
    
  },
  methods: {
    setExperiment(url){
      let index = url.indexOf(config.hardware_code_prefix);
      let length = config.hardware_code_prefix.length
      let experiment = url.substr(index, length + 2);
      this.$store.dispatch('setExperiment', experiment);
    },
    AddNewInputListeners(){
      //should check if new inputs exists that are not in the input_listener_ids array and add if not
      document.querySelectorAll('input').forEach(el => {
          if(el.id != '' && !this.input_listener_ids.includes(el.id)){
            console.log(el.id)
            this.input_listener_ids.push(el.id);
            this.AddInputChangeListener(el.id)
          }
        })
    },
    removeAllInputListeners(){
      this.input_listener_ids.forEach(id => {
        let el = document.getElementById(id);
        if(el != null){
          el.removeEventListener("change", this.createAndSendInputLog)
        }
      })
      this.input_listener_ids = []
    },
    AddButtonClickListener(id){
      const btn = document.getElementById(id);
      if(btn != null){
          btn.addEventListener("click", (event) => {
              let log = this.createClickLog(event);
              this.sendLog(log);
          });
      } else{
        console.log(`Button ${id} NOT MOUNTED`)
      }
  },
  createAndSendInputLog(event){
      let log = this.createInputLog(event);
      this.sendLog(log);
  },
  AddInputChangeListener(id){
      const btn = document.getElementById(id);
      if(btn != null){
          btn.addEventListener("change", this.createAndSendInputLog);
      } else{
        console.log(`Input ${id} NOT MOUNTED`)
      }
  },
  createAndSendMouseEnterLog(event){
    let log = this.createMouseEnterLog(event);
    this.sendLog(log);
  },
  AddMouseEnterListeners(){
    const drag_divs = document.querySelectorAll('[id^="drop_"]');
      drag_divs.forEach(div => {
          div.addEventListener("mouseenter", this.createAndSendMouseEnterLog);
      })
  },
  AddDragDropListeners(){
      const drag_divs = document.querySelectorAll('[id^="drop_"]');
      drag_divs.forEach(div => {
          div.addEventListener("dragstart", (event) => {
              let log = this.createDragEventLog(event);
              this.sendLog(log);
          });

          div.addEventListener("drop", (event) => {
              let log = this.createDropEventLog(event);
              this.sendLog(log);
          });
      })
  },
  AddHotkeyListener(){
      window.addEventListener("keydown", (event) => {
        if(config.hotkeys.includes(event.key)){
          let log = this.createHotkeyLog(event);
          this.sendLog(log);
        }
          
      });
  },
  AddIntervalLog(log){
      setInterval(() => {
        this.sendLog(log.payload);
      }, log.interval)
  },
  createAndSendSessionStartLog(){
    let log = this.createSessionStartLog();
    this.sendLog(log);
  },
  createAndSendComponentOpenedLog(element){
    let log = this.createComponentOpenLog(element);
    this.sendLog(log);
  },
  createAndSendComponentClosedLog(event){
    let log = this.createComponentClosedLog(event);
    this.sendLog(log);
  },
  createSessionStartLog(){
    let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "session-started", 
            "definition": `${this.instance_path}${config.definitions_path}/session-started`
          }, 
        "object": 
          {
            "ui": config.remote_lab_ui,
            "exp_id": this.getExperiment
          },
        "context": 
          {
            
          }
      }

      return log;
  },
    createClickLog(event){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "clicked", 
            "definition": `${this.instance_path}${config.definitions_path}/clicked`
          }, 
        "object": 
          {
            "id": event.target.id,
            "parent": event.target.parentNode ? event.target.parentNode.id : 'none',
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            "event_type": event.type,
            "event_timestamp": event.timeStamp,
            "x": event.clientX, 
            "y": event.clientY,
            "exp_id": this.getExperiment
          }
      }
      
      //IF the clicked target is associated with a graph node for TaskCompare, then add that information to context
      if(event.target.id in config.graph_nodes){
        log.context['graph_node'] = config.graph_nodes[event.target.id]
      }

      return log;
    },
    createMouseEnterLog(event){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "mouse-entered", 
            "definition": `${this.instance_path}${config.definitions_path}/mouse-entered`
          }, 
        "object": 
          {
            "id": event.target.id,
            "parent": event.target.parentNode.id,
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            "event_type": event.type,
            "event_timestamp": event.timeStamp,
            "mouse-left": event.relatedTarget != null ? event.relatedTarget.id : '',
            "exp_id": this.getExperiment
          }
      }

      return log;
    },
    createInputLog(event){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "changed", 
            "definition": `${this.instance_path}${config.definitions_path}/changed`,
          }, 
        "object": 
          {
            "id": event.target.id,
            "parent": event.target.parentNode.id,
            "ui": config.remote_lab_ui,
            "value": event.target.type == "checkbox" || event.target.type == "radio" ? event.target.checked : event.target.value
          },
        "context": 
          {
            "event_type": event.type,
            "event_timestamp": event.timeStamp,
            "exp_id": this.getExperiment
          }
      }

      //IF updating this input is associated with sending a hardware command and a graph node for TaskCompare, then add that information to context
      if(event.target.id in config.graph_nodes){
        log.context['graph_node'] = config.graph_nodes[event.target.id]
      }

      return log;
    },
    createHotkeyLog(event){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "pressed-hotkey", 
            "definition": `${this.instance_path}${config.definitions_path}/pressed-hotkey`
          }, 
        "object": 
          {
            "id": event.key,
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            "event_type": event.type,
            "event_timestamp": event.timeStamp,
            "previous_click": event.originalTarget.id,
            "exp_id": this.getExperiment
          }
      }

      //IF pressing this hotkey is associated with sending a hardware command and a graph node for TaskCompare, then add that information to context
      if(event.key in config.graph_nodes){
        log.context['graph_node'] = config.graph_nodes[event.key]
      }

      return log;
    },
    createDragEventLog(event){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "dragged-component", 
            "definition": `${this.instance_path}${config.definitions_path}/dragged-component`
          }, 
        "object": 
          {
            "id": event.target.id,
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            "event_type": event.type,
            "event_timestamp": event.timeStamp,
            "exp_id": this.getExperiment
          }
      }

      return log;
    },
    createDropEventLog(event){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "dropped-component", 
            "definition": `${this.instance_path}${config.definitions_path}/dropped-component`
          }, 
        "object": 
          {
            "id": event.target.id,
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            "event_type": event.type,
            "event_timestamp": event.timeStamp,
            "exp_id": this.getExperiment
          }
      }

      return log;
    },
    //check details of this log
    createSessionExpiredLog(){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": "system",
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "session-expired", 
            "definition": `${this.instance_path}${config.definitions_path}/session-expired`
          }, 
        "object": 
          {
            "exp_id": this.getExperiment,
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            
          }
      }

      return log;
    },
    createExperimentLog(message){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": message.level,
        "type": "experiment", 
        "actor":
          {
            "id": this.getExperiment,
            "hardware": this.getHardware,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "experiment-error", 
            "definition": `${this.instance_path}${config.definitions_path}/experiment-error`
          }, 
        "object": 
          {
            "id": '',
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            "msg": message.text
          }
      }

      return log;
    },
    createComponentOpenLog(element){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "opened-component", 
            "definition": `${this.instance_path}${config.definitions_path}/opened-component`
          }, 
        "object": 
          {
            "id": element.id,
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            "exp_id": this.getExperiment
          }
      }

      return log;
    },
    createComponentClosedLog(element){
      let log = {
        "timestamp": new Date().getTime(), 
        "level": "INFO",
        "type": "analytics", 
        "actor":
          {
            "id": this.getLogUUID,
            "course": this.getCourse
          },
        "verb": 
          {
            "name": "closed-component", 
            "definition": `${this.instance_path}${config.definitions_path}/closed-component`
          }, 
        "object": 
          {
            "id": element.id,
            "ui": config.remote_lab_ui
          },
        "context": 
          {
            "exp_id": this.getExperiment
          }
      }

      return log;
    },
    sendLog(log){
      if(this.getLogConsent){
        var accessURL = `${this.instance_path}${config.logging_path}?username=${this.getLogUUID}&course=${this.getCourse}&hardware=${this.getHardware}`; 
        axios
        .post(accessURL, 
              log, 
              { headers: 
                { 
                  'Content-Type': 'application/json',
                  'Authorization': 'Basic ' + this.la_auth
                } 
        }).then((response) => {
            //console.log(response)
        })
        .catch((err) => console.log(err));
      } 
        
    },
    printLog(log){
      console.log(log)
    }
      
      
  }
}
</script>

<style scoped>


</style>