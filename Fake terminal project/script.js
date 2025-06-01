const term = new Terminal({
  cursorBlink: true,
  fontSize: 20,
  theme: {
    background: '#000000',
    foreground: '#6d0000'
  }
});
term.open(document.getElementById('terminal'));
term.write('Welcome to the Terminal Forum!\r\n');
term.prompt = () => {
  term.write('\r\n> ');
};
term.prompt();

let input = '';

term.onKey(e => {
  const ev = e.domEvent;
  const key = e.key;
  if (ev.keyCode === 13) {
    // ENTER pressed
    handleCommand(input.trim());
    input = '';
    term.prompt();
  } else if (ev.keyCode === 8) {
    // BACKSPACE
    if (input.length > 0) {
      input = input.slice(0, -1);
      term.write('\b \b');
    }
  } else {
    input += key;
    term.write(key);
  }
});


function handleCommand(command) {
  if (command === 'help') {
    term.writeln('\r\nAvailable commands: post, list, clear, help');
  } else if (command === 'post') {
    term.writeln('\r\nEnter your message: (not implemented yet)');
  } else if (command === 'list') {
    term.writeln('\r\nPosts:\n1. Hello World!');
  } else if (command === 'clear') {
    term.clear();
  } else {
    term.writeln(`\r\nUnknown command: ${command}`);
  }
}
