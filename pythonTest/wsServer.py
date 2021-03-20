import asyncio
import websockets

async def echo(websocket, path):
    async for message in websocket:
        print("recv << " + message)
        message = "I got your message: {}".format(message)
        print('send >> ' + message)
        await websocket.send(message)

if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(websockets.serve(echo, '192.168.0.178', 9002))
    asyncio.get_event_loop().run_forever()