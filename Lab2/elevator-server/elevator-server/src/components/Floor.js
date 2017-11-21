const React = require("react");
const addons = require("react-addons");

const classSet = addons.classSet;


module.exports = class Floor extends React.Component {
  constructor(props) {
    super(...arguments);
   	this.state = {
      floorNum: props.floorNum,
   		up: false,
   		down: false
   	};
  }

  goUp(){
    console.log("success up")
    if(!this.state.up){
      this.setState({
        floorNum: this.state.floorNum,
        up: true,
        down: this.state.down
      })
    }
  }

  goDown(){
    console.log("success down")
    if(!this.state.down){
      this.setState({
        floorNum: this.state.floorNum,
        up: this.state.down,
        down: true
      })
    }
  }

  render() {
    var upClass = classSet({
      'floor-btn': true,
      'chosen': this.state.up
    });
    var downClass = classSet({
      'floor-btn': true,
      'chosen': this.state.down
    });
    return (
      <div className="column-box floor">
        <div className={upClass} onClick={this.goUp}>上</div>
        <div className={downClass} onClick={this.goDown}>下</div>
      </div>
    );
  }
};