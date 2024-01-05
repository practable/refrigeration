



import asyncio
import websockets
import json
import threading
import time
import datetime

import acGlobals as glbs



class sockServer:
    def __init__(self):
        print("starting Websocket Server")



    async def run(self, websocket, path):
            while True:
                try:
                    # await check_user_permit(websocket)
                    # TODO there was no await here but it told me to put one
                    await asyncio.gather(self.send_data(websocket))  # asyncio.gather(func1(),func2()) can gather different function and
                    # run together # seems just can be run once
                    await self.recv_user_msg(websocket)
                except websockets.ConnectionClosed:
                    print("ConnectionClosed...", path)
                    #print("websocket_users old:", websocket_users)
                    #websocket_users.remove(websocket)
                    #print("websocket_users new:", websocket_users)
                    break
                except websockets.InvalidState:
                    print("InvalidState...")
                    break
                except Exception as e:
                    print("Exception:", e)

    # regularly send message to client(2s), the loop will break until check client failed
    async def send_data(self, ws):
        while True:
            try:
                data = json.loads(json.dumps(glbs.acUnit_dictionary))
                dataPh = json.dumps(data, ensure_ascii=False)
                await ws.send(dataPh)
                await asyncio.sleep(2)
            except:
                print("check client failed")
                break

    async def recv_user_msg(self, websocket):
        while True:
            recv_text = await websocket.recv()
            print("recv_text:", websocket.pong, recv_text)
            response_text = f"Server return: {recv_text}"
            print("response_text:", response_text)
            await websocket.send(response_text)

server = sockServer()

if __name__ == '__main__':
    print("127.0.0.1:8181 websocket...")
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    try:
        #asyncio.run(websockets.serve(server.run("127.0.0.1", 8181)))
        asyncio.get_event_loop().run_until_complete(websockets.serve(server.run, "127.0.0.1", 8181))
        asyncio.get_event_loop().run_forever()
    except DeprecationWarning:
        print("I dont care")