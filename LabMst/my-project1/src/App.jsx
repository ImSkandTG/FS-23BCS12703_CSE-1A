import React from "react";
import StudentCard from "./components/StudentCard";

const students = [
  { name: "Amit Sharma", rollNo: "101", course: "B.Tech CSE" },
  { name: "Priya Singh", rollNo: "102", course: "B.Sc Physics" },
  { name: "Rahul Verma", rollNo: "103", course: "B.Com" },
];

function App() {
  return (
    <div className="min-h-screen bg-white flex flex-col items-center justify-center">
      <h1 className="text-3xl font-extrabold mb-8 text-green-700 tracking-wide font-sans">
        Student Identity Cards
      </h1>
      <div className="flex flex-wrap justify-center gap-8">
        {students.map((student) => (
          <StudentCard
            key={student.rollNo}
            name={student.name}
            rollNo={student.rollNo}
            course={student.course}
          />
        ))}
      </div>
      <p className="mt-6 text-gray-400 text-sm font-sans">
        Click a card to zoom in/out
      </p>
    </div>
  );
}

export default App;