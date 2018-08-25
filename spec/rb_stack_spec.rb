require 'spec_helper'
require_relative '..//lib/rb_fifo.rb'

RSpec.describe do
  let(:base_stack) { RBFifo.new }

  describe '#initialize' do

    context 'with depth' do
      subject { base_stack.depth }
      it { is_expected.to eq 0 }
    end
  end

  describe '#push' do
    let(:stack) { base_stack.push(:foo) }

    subject { stack }
    it { is_expected.to eq(stack) }

    context 'with value' do
      subject { stack.value }
      it { is_expected.to eq :foo }
    end

    context 'with depth' do
      subject { stack.depth }
      it { is_expected.to eq 1 }

      context 'when iterated' do
        subject { stack.push('bar').depth }
        it { is_expected.to eq(2) }
      end
    end
  end

  describe '#pop' do
    before do
      base_stack.push(:foo)
    end

    let!(:element) { base_stack.pop }
    subject { base_stack.value }
    it { is_expected.to eq(nil) }

    context 'with value' do
      subject { element }
      it { is_expected.to eq(:foo) }
    end

    context 'with depth' do
      subject { base_stack.depth }
      it { is_expected.to eq(0) }
    end

    context 'when popped twice' do
      let!(:second_element) { base_stack.pop }
      subject { base_stack.value }
      it { is_expected.to eq(nil) }

      context 'with value' do
        subject { second_element }
        it { is_expected.to eq(nil) }
      end
  
      context 'with depth' do
        subject { base_stack.depth }
        it { is_expected.to eq(0) }
      end

      context 'when popped further' do
        let!(:third_element) { base_stack.pop }
        subject { base_stack.value }
        it { is_expected.to eq(nil) }

        context 'with value' do
          subject { third_element }
          it { is_expected.to eq(nil) }
          it { expect { subject }.not_to raise_error }
        end
    
        context 'with depth' do
          subject { base_stack.depth }
          it { is_expected.to eq(0) }
          it { expect { subject }.not_to raise_error }
        end
      end
    end
  end
end

