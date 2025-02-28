import { createApp } from 'vue'
import App from './App.vue'
import store from './store'

import 'bootstrap';
import "bootstrap/dist/css/bootstrap.min.css";
import "bootstrap/dist/css/bootstrap-grid.min.css";
import 'es6-promise/auto'

// Load CSS style sheets for main components
// import '@/styles/app.css'
import '@/styles/theme-default.css'

const app = createApp(App)
app.use(store)
app.mount('#app')

