import React, { useState } from "react";

const StudentCard = ({ name, rollNo, course }) => {
  const [zoomed, setZoomed] = useState(false);

  return (
    <div
      className={`
        bg-green-100 border border-green-300 rounded-2xl shadow-xl p-6 w-80 cursor-pointer
        flex flex-col items-center transition-transform duration-300 relative
        ${zoomed ? "scale-110 z-20 ring-4 ring-green-200" : "scale-100"}
        hover:scale-105
      `}
      style={{
        fontFamily: "Inter, sans-serif",
        minHeight: "240px",
      }}
      onClick={() => setZoomed((z) => !z)}
    >
      {/* Decorative bar */}
      <div className="absolute top-0 left-0 w-full h-3 rounded-t-2xl bg-gradient-to-r from-green-300 via-green-200 to-green-400" />
      {/* Avatar */}
      <div className="w-20 h-20 bg-green-200 rounded-full flex items-center justify-center mb-4 mt-4 border-2 border-green-300 shadow">
        <span className="text-3xl font-bold text-green-700">
          {name[0]}
        </span>
      </div>
      {/* Details */}
      <div className="w-full text-center mt-2">
        <h2 className="text-xl font-semibold text-green-800 mb-1">{name}</h2>
        <div className="flex justify-between text-sm text-gray-700 mb-1 px-4">
          <span className="font-medium">Roll No:</span>
          <span>{rollNo}</span>
        </div>
        <div className="flex justify-between text-sm text-gray-700 px-4">
          <span className="font-medium">Course:</span>
          <span>{course}</span>
        </div>
      </div>
      {/* ID Label */}
      <div className="absolute top-3 right-5 text-xs text-green-500 font-bold tracking-widest">
        STUDENT ID
      </div>
    </div>
  );
};

export default StudentCard;