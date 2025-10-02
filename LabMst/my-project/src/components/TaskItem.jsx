import React from "react";

const TaskItem = ({ task, onToggleComplete, onDelete }) => {
  return (
    <li className="flex items-center justify-between bg-white dark:bg-gray-800 px-4 py-2 rounded shadow">
      <div className="flex items-center">
        <input
          type="checkbox"
          checked={task.completed}
          onChange={() => onToggleComplete(task.id)}
          className="mr-3 accent-blue-500"
        />
        <span
          className={`${
            task.completed ? "line-through text-gray-400" : ""
          } text-lg`}
        >
          {task.text}
        </span>
      </div>
      <button
        onClick={() => onDelete(task.id)}
        className="ml-4 text-red-500 hover:text-red-700 font-bold"
        aria-label="Delete task"
      >
        ×
      </button>
    </li>
  );
};

export default TaskItem;