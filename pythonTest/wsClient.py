import asyncio
import websockets

async def hello(uri):
    async with websockets.connect(uri) as websocket:
        welcome_text = await websocket.recv()
        print('welcome is ' + welcome_text)

        await websocket.send('hello world')
        recv_text = await websocket.recv()
        print(recv_text)

if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(
        hello('ws://192.168.0.178:9002')
    )