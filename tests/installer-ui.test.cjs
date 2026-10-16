const fs=require('node:fs'),vm=require('node:vm'),assert=require('node:assert/strict'),{webcrypto}=require('node:crypto'),{parseHTML}=require('linkedom');
(async()=>{const {window}=parseHTML(fs.readFileSync('dist/install/index.html','utf8')),document=window.document;let writes=0,id='FM-1_7010200',saved={},fetches=0;
class Updater{async find(filter){const d={model:'FM-1',text:id};return !filter||filter(d)?{id:d,link:{close(){}}}:null;}async install(image,product,step){writes++;id=product;step('done',id);}}
const c={window,document,console,crypto:webcrypto,Uint8Array,Blob,URL,Date,JSON,setTimeout,Updater,localStorage:{getItem:k=>saved[k]??null,setItem:(k,v)=>saved[k]=v,removeItem:k=>delete saved[k]},navigator:{requestMIDIAccess:async()=>({inputs:new Map([['1',{state:'connected',name:'X0X FM-1'}]])}),locks:{request:async(name,opts,fn)=>fn({name})}},fetch:async path=>{fetches++;const b=fs.readFileSync('dist/install/'+path);return {ok:true,json:async()=>JSON.parse(b),arrayBuffer:async()=>b.buffer.slice(b.byteOffset,b.byteOffset+b.byteLength)};}};
vm.createContext(c);vm.runInContext(fs.readFileSync('dist/install/fm1pkg.js','utf8').replaceAll('export ',''),c);vm.runInContext(fs.readFileSync('dist/install/installer.js','utf8').replace(/^import .*;$/gm,'').replace('export async','async'),c);
for(let i=0;i<40&&fetches<3;i++)await new Promise(r=>setTimeout(r,10));await new Promise(r=>setTimeout(r,30));
assert.equal(writes,0);assert(document.getElementById('install').disabled);
await document.getElementById('connect').onclick();assert.equal(writes,0);assert(document.getElementById('device').textContent.includes('7010200'));
document.getElementById('ready').checked=true;document.getElementById('ready').onchange();assert.equal(document.getElementById('install').disabled,false);
await document.getElementById('install').onclick();assert.equal(writes,1);assert.equal(id,'FM-1_7080001');assert(!saved['evolved-pending']);assert.equal(document.getElementById('progress').value,100);
await vm.runInContext(`checkedPackage(new Uint8Array(1000),'bad','FM-1_7080001').then(()=>{throw Error('bad hash accepted')},()=>{})`,c);
const stock=document.querySelector('[value=stock]');stock.onchange();assert(document.getElementById('install').disabled);assert.equal(writes,1);
console.log('PASS installer DOM: no auto-flash, read-only connect, explicit acknowledgement, successful state, bad hash rejected, original firmware unavailable until verified. Mock device; not browser/USB QA.');})().catch(e=>{console.error(e);process.exit(1)});
