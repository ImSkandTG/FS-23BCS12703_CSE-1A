const fs = require("fs");
function readProblem() {
    return new Promise(function(resolve) {
        fs.readFile("input.txt","utf-8",(err,data) => {
            resolve(data);
        })
    })
}
function WriteSolution(solution) {
    return new Promise(function() {
        fs.writeFile('output.txt',solution,'utf-8',(err)=> {
            if (err) console.log("Error Found");
            else console.log("Solution Updated!");
        })
    })
}
function basicCalculator(equation) {
    let result  = Number(equation[0]), opi = 1;
    let op = equation[opi];
    for (let i=1;i<equation.length;i+=2) {
        opi = i;
        op = equation[i];
        let prev = Number(equation[opi+1]);
        let ind = opi+2;
        if (op==='+' || op==='-') {
            while (ind<equation.length && (equation[ind]!=='+' && equation[ind]!=='-')) {
                if (equation[ind]==='*') prev=prev*Number(equation[ind+1]);
                else if (equation[ind]==='/') prev/=Number(equation[ind+1]);
                ind+=2;
            }
            if (op==='+') result+=prev;
            else result-=prev;
            i = ind-2;
        }
        else if (op==='*') result*=prev;
        else result/=prev;
    }
    return result;
}
parseString = (s,index) => {
    let sm = "";
    for (let i = index; i < s.length; i++) {
        if (s[i]==='(') {
            sm = sm+' '+parseString(s,i+1);
            let count = 1;
            while (count!==0) {
                i++;
                if (s[i]==='(') count++;
                else if (s[i]===')') count--;
            }
            continue;
        }
        if (s[i]===')') break;
        if (s[i] === '*' || s[i] === '/' || s[i] === '+' || s[i] === '-') sm += ' ';
        sm += s[i];
        if (s[i] === '*' || s[i] === '/' || s[i] === '+' || s[i] === '-') sm += ' ';
    }
    sm = sm.split(" ");
    sm = sm.filter(digit => digit !== '');
    return basicCalculator(sm).toString();
}
async function main(){
    let eqn = (await readProblem()).trim();
    return await WriteSolution(parseString(eqn, 0));
}
main();