

const streamStore = {
  state: {
    connectionDroppedAt: 0,
    connectionIsDropped: false,
    lastVideoCheck: 0,
    lastVideoWrite: 0,
    streams: [],
    streamsObtained: false,
    videoURL: "",
    videoURLObtained: false,
    videoBURL: "",
    videoBURLObtained: false,
    videoCURL: "",
    videoCURLObtained: false,
    dataURL: " ",
    dataURLObtained: false,
    logURL: "",
    logURLObtained: false,
    remoteLabVersion: '',
    disableTooltips: false,
    expiryTime: '',
    camera: '',
    sessionExpired: false,
  },
  mutations: {
    SET_CONNECTION_DROPPED_AT(state, when) {
      state.connectionDroppedAt = when;
    },
    SET_CONNECTION_IS_DROPPED(state, isDropped) {
      state.connectionIsDropped = isDropped;
    },
    SET_LAST_VIDEO_CHECK(state, when) {
      state.lastVideoCheck = when;
    },
    SET_LAST_VIDEO_WRITE(state, when) {
      state.lastVideoWrite = when;
    },
    DELETE_STREAMS(state) {
      state.streams = {};
      state.streamsObtained = false;
    },
    SET_STREAMS(state, streams) {
      state.streams = streams;
      state.streamsObtained = true;
    },
    SET_VIDEO_URL(state, url) {
      state.videoURL = url;
      state.videoURLObtained = true;
    },
    DELETE_VIDEO_URL(state) {
      state.videoURL = "";
      state.videoURLObtained = false;
    },
    SET_VIDEO_B_URL(state, url) {
      state.videoBURL = url;
      state.videoBURLObtained = true;
    },
    DELETE_VIDEO_B_URL(state) {
      state.videoBURL = "";
      state.videoBURLObtained = false;
    },
    SET_VIDEO_C_URL(state, url) {
      state.videoCURL = url;
      state.videoCURLObtained = true;
    },
    DELETE_VIDEO_C_URL(state) {
      state.videoCURL = "";
      state.videoCURLObtained = false;
    },
    SET_DATA_URL(state, url) {
      state.dataURL = url;
      state.dataURLObtained = true;
    },
    DELETE_DATA_URL(state) {
      state.dataURL = "";
      state.dataURLObtained = false;
    },
    SET_LOG_URL(state, url) {
      state.logURL = url;
      state.logURLObtained = true;
    },
    DELETE_LOG_URL(state) {
      state.logURL = "";
      state.logURLObtained = false;
    },
    SET_REMOTE_LAB_VERSION(state, version) {
      state.remoteLabVersion = version;
    },
    SET_DATA_RECORDER(state, set) {
      state.isDataRecorderOn = set;
    },
    SET_DISABLE_TOOLTIPS(state, set) {
      state.disableTooltips = set;
    },
    SET_EXPIRY_TIME(state, time) {
      state.expiryTime = time;
    },
    SET_CAMERA(state, cam) {
      state.camera = cam;
    },
    SET_SESSION_EXPIRED(state, set) {
      state.sessionExpired = set;
    },
  },
  actions: {
    setConnectionDroppedAt(context, when) {
      context.commit("SET_CONNECTION_DROPPED_AT", when);
    },
    setConnectionIsDropped(context, isDropped) {
      context.commit("SET_CONNECTION_IS_DROPPED", isDropped);
    },
    setLastVideoCheck(context, when) {
      context.commit("SET_LAST_VIDEO_CHECK", when);
    },
    setLastVideoWrite(context, when) {
      context.commit("SET_LAST_VIDEO_WRITE", when);
    },
    deleteStreams(context) {
      context.commit("DELETE_STREAMS");
    },
    setStreams(context, streams) {
      context.commit("SET_STREAMS", streams);
    },
    setVideoURL(context, url) {
      context.commit("SET_VIDEO_URL", url);
    },
    deleteVideoURL(context) {
      context.commit("DELETE_VIDEO_URL");
    },
    setVideoBURL(context, url) {
      context.commit("SET_VIDEO_B_URL", url);
    },
    deleteVideoBURL(context) {
      context.commit("DELETE_VIDEO_B_URL");
    },
    setVideoCURL(context, url) {
      context.commit("SET_VIDEO_C_URL", url);
    },
    deleteVideoCURL(context) {
      context.commit("DELETE_VIDEO_C_URL");
    },
    setDataURL(context, url) {
      context.commit("SET_DATA_URL", url);
    },
    deleteDataURL(context) {
      context.commit("DELETE_DATA_URL");
    },
    setLogURL(context, url) {
      context.commit("SET_LOG_URL", url);
    },
    deleteLogURL(context) {
      context.commit("DELETE_LOG_URL");
    },
    setRemoteLabVersion(context, version) {
      context.commit("SET_REMOTE_LAB_VERSION", version);
    },
    setDataRecorder(context, set) {
      context.commit("SET_DATA_RECORDER", set);
    },
    setDisableTooltips(context, set) {
      context.commit("SET_DISABLE_TOOLTIPS", set);
    },
    setExpiryTime(context, time) {
      context.commit("SET_EXPIRY_TIME", time);
    },
    setCamera(context, cam) {
      context.commit("SET_CAMERA", cam);
    },
    setSessionExpired(context, set) {
      context.commit('SET_SESSION_EXPIRED', set);
    }

  },
  getters: {
    getStreamsObtained(state) {
      return state.streamsObtained;
    },
    getStreams(state) {
      return state.streams;
    },
    getStream: (state) => (what) => {
      if (state.streams != null) {
        if (!state.streamsObtained) {
          return {};
        }
        var results = state.streams.filter((obj) => {
          return obj.for == what;
        });
        if (results.length < 1) {
          return {};
        } else {
          return results[0];
        }
      } else {
        return {};
      }
    },
    getVideoURL(state) {
      return state.videoURL;
    },
    getVideoURLObtained(state) {
      return state.videoURLObtained;
    },
    getVideoBURL(state) {
      return state.videoBURL;
    },
    getVideoBURLObtained(state) {
      return state.videoBURL;
    },
    getVideoCURL(state) {
      return state.videoCURL;
    },
    getVideoCURLObtained(state) {
      return state.videoCURL;
    },
    getDataURL(state) {
      return state.dataURL;
    },
    getDataURLObtained(state) {
      return state.dataURLObtained;
    },
    getLogURL(state) {
      return state.logURL;
    },
    getLogURLObtained(state) {
      return state.logURLObtained;
    },
    getRemoteLabVersion(state) {
      return state.remoteLabVersion;
    },
    getDisableTooltips(state) {
      return state.disableTooltips;
    },
    getExpiryTime(state) {
      return state.expiryTime;
    },
    getConnectionDroppedAt(state) {
      return state.connectionDroppedAt;
    },
    getConnectionIsDropped(state) {
      return state.connectionIsDropped;
    },
    getLastVideoCheck(state) {
      return state.lastVideoCheck;
    },
    getLastVideoWrite(state) {
      return state.lastVideoWrite;
    },
    getCamera(state) {
      return state.camera;
    },
    getSessionExpired(state) {
      return state.sessionExpired;
    }



  },
}

export default streamStore;
