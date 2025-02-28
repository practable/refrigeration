import { createRouter, createWebHistory } from 'vue-router'
import enthalpy from '../components/ping.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/enthalpy',
      name: 'enthalpy',
      component: enthalpy
    },
  ]
})

export default router