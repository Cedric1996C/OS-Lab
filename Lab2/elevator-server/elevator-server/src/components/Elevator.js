const React = require("react");
const addons = require("react-addons");

const classSet = addons.classSet;


module.exports = class Elevator extends React.Component {
  constructor() {
    super(...arguments);
   	this.state = {
      door: "打开",
   		up: null,
   		down: true
   	};
  }

  render() {
    return (
      <div className="column-box elevator">
        <div className="door-state">状态：{this.state.door}</div>
        <div className="elevator-state"></div>
        <div className="elevator-state"></div>
        <div className="elevator-state"></div>
      </div>
    );
  }
};