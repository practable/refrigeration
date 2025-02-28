// vue.config.js
module.exports = {
    // options...
    runtimeCompiler: true,
    publicPath: process.env.NODE_ENV === 'production'
    ? '/ui/fridge-gunt-default-1.0/'
    : '/'
  }
  