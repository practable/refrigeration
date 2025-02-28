
import { createApp } from 'vue'
import App from './App.vue'
import store from "./store.js";

import 'bootstrap';
import "bootstrap/dist/css/bootstrap.min.css";
import 'es6-promise/auto'

import '@/styles/app.css'

const app = createApp(App)

app.use(store)
app.mount('#app')

