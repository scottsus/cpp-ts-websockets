import React, { useEffect, useState } from 'react';
import logo from './logo.svg';
import './App.css';

function App() {
  const [positionalData, setPositionalData] = useState<string[]>([]);

  useEffect(() => {
    const ws = new WebSocket('ws://localhost:9002');

    ws.onopen = () => {
      console.log('Connected to the websocket server');
    };

    ws.onmessage = (event) => {
      setPositionalData((prevData) => [...prevData, event.data]);
    };

    ws.onclose = () => {
      console.log('Disconnected from the websocket server');
    };

    ws.onerror = (error) => {
      console.error('WebSocket error:', error);
    };

    return () => {
      ws.close();
    };
  }, []);

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.tsx</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
        <div>
          <h2>Positional Data:</h2>
          <ul>
            {positionalData.map((data, index) => (
              <li key={index}>{data}</li>
            ))}
          </ul>
        </div>
      </header>
    </div>
  );
}

export default App;
