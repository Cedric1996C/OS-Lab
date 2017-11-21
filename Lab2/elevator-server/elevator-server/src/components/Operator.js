const React = require("react");
const addons = require("react-addons");

const classSet = addons.classSet;

const Elevator = require('./Elevator');
const Floor = require('./Floor')

module.exports = class Operator extends React.Component {
  constructor() {
    super(...arguments);
 	this.state = {
 		up: null,
 		down: true
 	};
  }

  // handleUserLogout() {
  //   AuthStore.logout();
  // }

  // getFooter() {
  //   return (
  //     <div className="button-collection flush-bottom">
  //       <button
  //         className="button button-primary"
  //         onClick={this.handleUserLogout}
  //       >
  //         Log out
  //       </button>
  //     </div>
  //   );
  // }

  render() {
    return (
      <div className="row-box operator-frame">
       	<div className="row-box floor-operator">
       		<div className="column-box floor-controller">
       			<div className="notice">楼层控制</div>
       			<Floor floorNum='3'/>
       			<Floor floorNum='2'/>
       			<Floor floorNum='1'/>
       		</div>
       		<div className="column-box elevator-controller">
       			<div className="notice">电梯控制</div>
       			<div className="floor-num">3</div>
       			<div className="floor-num">2</div>
       			<div className="floor-num">1</div>
       			<div className="column-box floor">
			        <div className="floor-btn">开</div>
			        <div className="floor-btn">关</div>
		      </div>
       		</div>
       	</div>
       	<Elevator/>
      </div>
    );
  }
};